/*
** client_manager.cc
** Login : <elthariel@rincevent>
** Started on  Wed Mar  2 19:47:37 2011 elthariel
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
#include "client_manager.hh"

using namespace std;

namespace e2
{
  client_manager::client_manager(stream_manager &sm)
    : m_streams(sm)
  {
  }

  client_manager::~client_manager()
  {
  }

  bool                client_manager::on_connection(net::connection &conn)
  {
    boost::mutex::scoped_lock l(m_mutex);

    client_ptr        c(new client(m_streams, *this, conn));

    if (c)
    {
      m_clients.push_back(c);
      return true;
    }
    else
      return false;
  }
};

