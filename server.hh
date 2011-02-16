/*
** server.hh
** Login : <elthariel@rincevent>
** Started on  Wed Feb  9 15:21:18 2011 elthariel
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

#ifndef   	SERVER_HH_
# define   	SERVER_HH_

# include <boost/utility.hpp>

# include "types.hh"
# include "connection.hh"

namespace e2
{
  namespace net
  {
    class server : public boost::noncopyable
    {
    public:
      server(std::string host, unsigned short port);

      boost::asio::io_service           &io();
      boost::asio::ssl::context         &ssl();
    protected:
      void                              start_accept();
      void                              handle_accept(connection* new_connection,
                                                      const boost::system::error_code& error);
      std::string                       get_password() const;

      boost::asio::io_service           m_io_service;
      boost::asio::ip::tcp::acceptor    m_acceptor;
      boost::asio::ssl::context         m_ssl_context;
    private:
      server();
    };
  }
}

#endif	    /* !SERVER_HH_ */
