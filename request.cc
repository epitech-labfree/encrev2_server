/*
** request.cc
** Login : <elthariel@rincevent>
** Started on  Thu Feb 24 17:40:07 2011 elthariel
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
#include "request.hh"

namespace e2
{
  bool                request::is_valid()
  {
    return get_type() != UNKNOWN;
  }

  bool                request::has_key(std::string k)
  {
    return find(k) != end();
  }

  request::type       request::get_type()
  {
    std::string       action;

    action = (*this)["action"];

    if (action == "READ")
      return READ;
    else if (action == "WRITE")
      return WRITE;
    else
      return UNKNOWN;
  }
}
