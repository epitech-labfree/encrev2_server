/*
** e2.c
** Login : <elthariel@rincevent>
** Started on  Thu Feb 24 06:13:17 2011 elthariel
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
#include <string>

#include "e2.hh"

using namespace std;

namespace e2
{
  e2::e2(po::variables_map &vm)
    : m_server(vm["ssl-key"].as<string>(),
               vm["ssl-crt"].as<string>(),
               vm["ssl-dh"].as<string>(),
               vm["bind"].as<string>(),
               vm["port"].as<int>())
  {
  }

  e2::~e2()
  {
  }

  void                        e2::run()
  {
    m_server.io().run();
  }
}
