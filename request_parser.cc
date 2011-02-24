/*
** request_parser.cc
** Login : <elthariel@rincevent>
** Started on  Thu Feb 24 17:39:30 2011 elthariel
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
#include "request_parser.hh"

namespace e2
{
  request_parser::request_parser()
  {
  }

  bool                request_parser::feed(net::const_buffer_ptr data)
  {
  }

  bool                request_parser::is_complete()
  {
  }

  request_parser::operator bool()
  {
    return is_complete();
  }

  request             &request_parser::get_request()
  {
    return m_request;
  }
}
