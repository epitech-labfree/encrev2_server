/*
** connection.cc
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
    connection::connection(boost::asio::io_service& io_service,
                           boost::asio::ssl::context& context)
      : m_socket(io_service, context)
    {
    }

    connection::~connection()
    {
      cout << "connection deleted" << endl;
    }

    ssl_socket::lowest_layer_type &connection::socket()
    {
      return m_socket.lowest_layer();
    }

    void                  connection::start()
    {
      m_socket.async_handshake(boost::asio::ssl::stream_base::server,
                               boost::bind(&connection::handle_handshake, this,
                                           boost::asio::placeholders::error));
    }

    void connection::handle_handshake(const boost::system::error_code& error)
    {
      m_msg = string("Ceci est un test\n");

      if (!error)
      {
        boost::asio::async_write(m_socket, boost::asio::buffer(m_msg),
                                 boost::bind(&connection::handle_write, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
        m_socket.async_read_some(boost::asio::buffer(m_data, max_length),
                                 boost::bind(&connection::handle_read, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
      }
      else
        cerr << "SSL Handshake error: " << error.message() << endl;
    }

    void connection::handle_read(const boost::system::error_code& error,
                                 size_t bytes_transferred)
    {
      if (!error)
      {
        boost::asio::async_write(m_socket,
                                 boost::asio::buffer(m_data, bytes_transferred),
                                 boost::bind(&connection::handle_write, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
      }
      else
      {
        cerr << "handle_read error: " << error.message() << endl;
        delete this;
      }
    }

    void connection::handle_write(const boost::system::error_code& error,
                                  size_t bytes_transferred)
    {
      if (!error)
      {
        m_socket.async_read_some(boost::asio::buffer(m_data, max_length),
                                 boost::bind(&connection::handle_read, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
      }
      else
      {
        cerr << "handle_write error: " << error.message() << endl;
        delete this;
      }
    }
  }
}
