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
      connection(boost::asio::io_service& io_service,
                 boost::asio::ssl::context& context);
      ~connection();

      ssl_socket::lowest_layer_type     &socket();
      void                              start();

    protected:
      void handle_handshake(const boost::system::error_code& error);
      void handle_write(const boost::system::error_code& error,
                        size_t bytes_transferred);
      void handle_read(const boost::system::error_code& error,
                       size_t bytes_transferred);

      enum { max_length = 1024 };
      ssl_socket                m_socket;
      std::string               m_msg;
      char                      m_data[max_length];
    };
  }
}
#endif	    /* !CONNECTION_HH_ */
