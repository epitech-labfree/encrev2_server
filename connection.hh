/*
** connection.hh
** Login : <elthariel@rincevent>
** Started on  Wed Feb  9 15:25:09 2011 elthariel
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

#ifndef   	CONNECTION_HH_
# define   	CONNECTION_HH_

# include <boost/bind.hpp>

# include "types.hh"

namespace e2
{
  namespace net
  {
    class receiver
    {
    public:
      virtual ~receiver() {}

      virtual bool                      receive_data(const_buffer_ptr data) = 0;
    };

    class connection
    {
    public:
      virtual ~connection() {}

      virtual bool                      send_data(const_buffer_ptr data) = 0;
      virtual bool                      set_receiver(receiver *r) = 0;
    };

    class ssl_connection : public connection
    {
    public:
      enum {READ_SIZE = 1024};

      ssl_connection(boost::asio::io_service& io_service,
                 boost::asio::ssl::context& context);
      ~ssl_connection();

      ssl_socket::lowest_layer_type     &socket();
      void                              start();

      bool                              send_data(const_buffer_ptr data_to_send);
      bool                              set_receiver(receiver *r);

    protected:
      void handle_handshake(const boost::system::error_code& error);
      void handle_write(const boost::system::error_code& error,
                        size_t bytes_transferred);
      void handle_read(const boost::system::error_code& error,
                       size_t bytes_transferred);
      void start_read();
      void start_write();

      ssl_socket                m_socket;
      const_buffer_list         m_buffers;
      buffer_ptr                m_input_buffer;
      boost::mutex              m_mutex;
      bool                      m_send_active, m_ready;

      receiver                  *m_receiver;
    };
  }
}
#endif	    /* !CONNECTION_HH_ */
