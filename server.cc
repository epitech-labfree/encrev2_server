/*
** server.cc
** Login : <elthariel@rincevent>
** Started on  Wed Feb  9 15:21:57 2011 elthariel
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
#include "server.hh"

namespace e2
{
  namespace net
  {
    server::server(std::string host, unsigned short port = 6666)
      : m_acceptor(m_io_service, tcp::endpoint(tcp::v4(), port)),
        m_ssl_context(m_io_service, boost::asio::ssl::context::sslv23)
    {
      m_ssl_context.set_options(boost::asio::ssl::context::default_workarounds
                                | boost::asio::ssl::context::no_sslv2
                                | boost::asio::ssl::context::single_dh_use);
      m_ssl_context.set_password_callback(boost::bind(&server::get_password, this));
      m_ssl_context.use_certificate_chain_file("ssl/cert.pem");
      m_ssl_context.use_private_key_file("ssl/privkey.pem", boost::asio::ssl::context::pem);
      m_ssl_context.use_tmp_dh_file("ssl/dhparams.pem");

      start_accept();
    }

    boost::asio::io_service           &server::io()
    {
      return m_io_service;
    }

    boost::asio::ssl::context         &server::ssl()
    {
      return m_ssl_context;
    }

    void server::start_accept()
    {
      connection* new_connection = new connection(io(), ssl());

      m_acceptor.async_accept(new_connection->socket(),
                              boost::bind(&server::handle_accept, this, new_connection,
                                          boost::asio::placeholders::error));
    }

    void server::handle_accept(connection* new_connection,
                               const boost::system::error_code& error)
    {
      if (!error)
      {
        new_connection->start();
        start_accept();
      }
    }

    std::string server::get_password() const
    {
      return "test";
    }

  }
}

