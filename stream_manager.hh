/*
** stream_manager.hh
** Login : <elthariel@rincevent>
** Started on  Thu Feb 24 06:03:36 2011 elthariel
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

#ifndef   	STREAM_MANAGER_HH_
# define   	STREAM_MANAGER_HH_

# include "types.hh"
# include "stream.hh"

namespace e2
{
  class stream_manager
  {
  public:
    typedef std::map<std::string, stream_ptr> stream_map;

    stream_manager();
    ~stream_manager();

    stream_ptr          create_stream(client &c, std::string name);
    void                delete_stream(std::string name);
    void                delete_stream(stream_ptr stream);

    stream_ptr          get_stream(std::string name);
    stream_ptr          operator[](std::string name); // handy alias for the above
    bool                exists(std::string name);

  protected:

    stream_map          m_streams;
    boost::mutex        m_mutex;
  };
};

#endif	    /* !STREAM_MANAGER_HH_ */
