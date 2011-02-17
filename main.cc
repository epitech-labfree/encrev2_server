/*
** main.cc
** Login : <elthariel@rincevent>
** Started on  Wed Feb  9 15:07:34 2011 elthariel
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

using namespace std;


int main(int ac, char **av)
{
  //  try
  {
    e2::net::server     server("ssl/privkey.pem", "ssl/cert.pem", "ssl/dhparams.pem",
                               string("unused_now"), 6666);

    cout << "Launching Encrev2 Server" << endl;
    server.io().run();
  }
  // catch (exception &e)
  // {
  //   cerr << av[0] << " aborted, exception.what() = " << e.what() << endl;
  // }


  return 0;
}

