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

#include "e2.hh"

using namespace std;

void                    set_options(po::options_description &desc)
{
  desc.add_options()
    ("help",                    "Produce help message")
    ("version",                 "Print version information")
    // Network stuffs
    ("port", po::value<int>()->default_value(6666),
                                "Bind server to the port 'arg'")
    ;

  cout << "THESE ARE JUST TEST, OPTIONS ARE STILL UNUSED" << endl;
  cout << desc << endl;
  cout << "-----------------------------" << endl;
};

po::variables_map       get_config(int ac, char **av)
{
  po::options_description desc("Usage");

  set_options(desc);
}

int main(int ac, char **av)
{

  try
  {
    po::variables_map   vm = get_config(ac, av);
    e2::e2              e2_server(vm);

    cout << "Launching Encrev2 Server" << endl;
    e2_server.run();
  }
  catch (exception &e)
  {
    cerr << av[0] << " aborted, exception.what() = " << e.what() << endl;
    return 1;
  }

  return 0;
}

