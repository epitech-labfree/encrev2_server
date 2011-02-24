/*
** client.hh
** Login : <elthariel@rincevent>
** Started on  Thu Feb 24 05:24:56 2011 elthariel
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

#include "client.hh"

using namespace std;

namespace e2
{
  client::client(stream_manager &sm, client_manager &cm, net::connection &c)
    : m_streams(sm), m_clients(cm), m_connnection(c)
  {
    m_connnection.set_receiver(this);
  }

  client::~client()
  {
  }

  bool                        client::receive_data(net::const_buffer_ptr data)
  {
  }
}