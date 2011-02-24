/*
** e2.hh
** Login : <elthariel@rincevent>
** Started on  Thu Feb 24 06:12:14 2011 elthariel
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

#ifndef   	E2_HH_
# define   	E2_HH_

# include <boost/program_options.hpp>

# include "server.hh"
# include "stream_manager.hh"
# include "client_manager.hh"

namespace po = boost::program_options;

namespace e2
{
  class e2
  {
  public:
    e2(po::variables_map &vm);
    ~e2();

    void                        run();

  protected:
    net::server                 m_server;
    // client_manager              m_clients;
    // stream_manager              m_streams;
  };
}

#endif	    /* !E2_HH_ */
