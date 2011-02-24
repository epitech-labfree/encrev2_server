/*
** ssl_connection.cc
** Login : <elthariel@rincevent>
** Started on  Wed Feb  9 15:26:51 2011 elthariel
** $Id$
**
** Author(s):
**  - elthariel <elthariel@gmail.com>
**
** Copyright (C) 2011 elthariel
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <iostream>
#include "connection.hh"

using namespace std;

namespace e2
{
  namespace net
  {
    ssl_connection::ssl_connection(boost::asio::io_service& io_service,
                                   boost::asio::ssl::context& context)
      : m_socket(io_service, context), m_send_active(false), m_ready(false),
        m_receiver(0)
    {
    }

    ssl_connection::~ssl_connection()
    {
      cout << "ssl_connection deleted" << endl;
    }

    ssl_socket::lowest_layer_type &ssl_connection::socket()
    {
      return m_socket.lowest_layer();
    }

    bool                  ssl_connection::send_data(const_buffer_ptr data)
    {
      boost::mutex::scoped_lock l(m_mutex);

      if (m_buffers.size() <= 64)
      {
        m_buffers.push_back(data);
        if (!m_send_active && m_ready)
          start_write();
        return true;
      }
      else
      {
        std::clog << "Ssl_Connection buffer list is full !" << std::endl;
        return false;
      }
    }

    bool                  ssl_connection::set_receiver(receiver *r)
    {
      m_receiver = r;

      return true;
    }

    void                  ssl_connection::start()
    {
      m_socket.async_handshake(boost::asio::ssl::stream_base::server,
                               boost::bind(&ssl_connection::handle_handshake, this,
                                           boost::asio::placeholders::error));
    }

    void                  ssl_connection::start_read()
    {
      if (m_ready)
      {
        buffer_ptr p(new buffer(READ_SIZE));
        m_input_buffer = p;
        m_socket.async_read_some(boost::asio::buffer(*m_input_buffer.get()),
                                 boost::bind(&ssl_connection::handle_read, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
      }
    }

    // You must own m_mutex, before calling this method.
    void                  ssl_connection::start_write()
    {
      if (m_ready && m_buffers.size() > 0)
      {
        const_buffer_ptr buf = *m_buffers.begin();
        boost::asio::async_write(m_socket, boost::asio::buffer(*buf.get()),
                                 boost::bind(&ssl_connection::handle_write, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
      }
    }

    void ssl_connection::handle_handshake(const boost::system::error_code& error)
    {
      if (!error)
      {
        boost::mutex::scoped_lock l(m_mutex);

        m_ready = true;

        if (m_buffers.size() > 0)
          start_write();
        start_read();
      }
      else
      {
        cerr << "SSL Handshake error: " << error.message() << endl;
        // FIXME Unhandled error.
      }
    }

    void ssl_connection::handle_read(const boost::system::error_code& error,
                                     size_t bytes_transferred)
    {
      if (!error)
      {
        std::clog << "Received some data !" << std::endl;
        if (m_receiver)
        {
          m_input_buffer->resize(bytes_transferred);
          m_receiver->receive_data(boost::const_pointer_cast<const buffer>(m_input_buffer));
        }
        start_read();
      }
      else
      {
        cerr << "handle_read error: " << error.message() << endl;
        // FIXME Unhandled error.
      }
    }

    void ssl_connection::handle_write(const boost::system::error_code& error,
                                      size_t bytes_transferred)
    {
      boost::mutex::scoped_lock l(m_mutex);

      if (!error)
      {
        m_buffers.pop_front();
        if (m_buffers.size() > 0)
          start_write();
      }
      else
      {
        cerr << "handle_write error: " << error.message() << endl;
        // FIXME Unhandled error.
      }
    }
  }
}
