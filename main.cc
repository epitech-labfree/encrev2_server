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
#include <string>

#include "e2.hh"

using namespace std;

void                    set_options(po::options_description &desc)
{
  desc.add_options()
    ("help",                    "Produce help message")
    ("version",                 "Print version information")
    // Network stuffs
    ("port", po::value<int>()->default_value(6666),
                                "Port to listen to")
    ("bind", po::value<string>()->default_value("0.0.0.0"),
                                "Ip address to bind to (unused)")
    // Ssl stuffs
    ("ssl-key", po::value<string>()->default_value("ssl/privkey.pem"),
                                "Path to ssl private key")
    ("ssl-crt", po::value<string>()->default_value("ssl/cert.pem"),
                                "Path to ssl certificate")
    ("ssl-dh", po::value<string>()->default_value("ssl/dhparams.pem"),
                                "Path to DH Params file")
    ;
};

bool                    short_run_option(po::options_description &desc,
                                         po::variables_map &vm)
{
  if (vm.count("help"))
    cout << desc << endl;
  else if (vm.count("version"))
  {
    cout << "e2_server: 0.0.0-alpha" << endl;
  }
  else
    return false;
  return true;
}

int main(int ac, char **av)
{
  po::options_description desc("Usage");
  set_options(desc);
  po::variables_map vm;

  try { po::store(po::parse_command_line(ac, av, desc), vm); }
  catch (...) {
    cerr << "Unrecognized command line parameter(s)" << endl
         <<  desc << endl;
    return (1);
  }

  po::notify(vm);

  if (!short_run_option(desc, vm))
  {
    try
    {
      e2::e2              e2_server(vm);

      cout << "Launching Encrev2 Server" << endl;
      e2_server.run();
    }
    catch (exception &e)
    {
      cerr << av[0] << " aborted, exception.what() = " << e.what() << endl;
      return 2;
    }
  }

  return 0;
}

