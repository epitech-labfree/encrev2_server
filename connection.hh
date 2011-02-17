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

# include <boost/asio.hpp>
# include <boost/bind.hpp>
# include <boost/shared_ptr.hpp>
# include <boost/enable_shared_from_this.hpp>

# include "types.hh"

namespace e2
{
  namespace net
  {
    class connection
    {
    public:
      typedef std::vector<uint8_t> buffer;
      typedef boost::shared_ptr<buffer> buffer_ptr;
      typedef boost::shared_ptr<const buffer> const_buffer_ptr;
      typedef std::list<const_buffer_ptr> buffer_list;
      typedef boost::signals2::signal<bool (buffer_ptr &)> data_available_signal;
      typedef boost::signals2::signal<void ()> connected_signal;
      typedef boost::signals2::signal<void ()> disconnected_signal;

      virtual ~connection(){}

      virtual void                              start() = 0;

      virtual data_available_signal             &on_data_received() = 0;
      virtual connected_signal                  &on_connect() = 0;
      virtual disconnected_signal               &on_disconnect() = 0;
      virtual bool                              send_data(const_buffer_ptr &data_to_send) = 0;
    };

    class ssl_connection : public connection
    {
    public:
      ssl_connection(boost::asio::io_service& io_service,
                     boost::asio::ssl::context& context);
      ~ssl_connection();

      ssl_socket::lowest_layer_type     &socket();
      void                              start();

      data_available_signal             &on_data_received();
      connected_signal                  &on_connect();
      disconnected_signal               &on_disconnect();
      bool                              send_data(buffer &data_to_send);

    protected:
      void handle_handshake(const boost::system::error_code& error);
      void handle_write(const boost::system::error_code& error,
                        size_t bytes_transferred);
      void handle_read(const boost::system::error_code& error,
                       size_t bytes_transferred);
      void start_write();

      ssl_socket                m_socket;
      buffer_list               m_buffer;
      //buffer                    m_input_buffer, m_output_buffer;
      boost::mutex              m_input_mutex, m_output_mutex;
      bool                      m_send_active;

      // std::string               m_msg;
      // char                      m_data[max_length];

      data_available_signal     m_data_signal;
      connected_signal          m_connected_signal;
      disconnected_signal       m_disconnected_signal;
    };
  }
}
#endif	    /* !CONNECTION_HH_ */
