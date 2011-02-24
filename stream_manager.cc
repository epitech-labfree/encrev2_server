/*
** stream_manager.cc
** Login : <elthariel@rincevent>
** Started on  Thu Feb 24 08:50:40 2011 elthariel
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
#include "stream_manager.hh"

using namespace std;

namespace e2
{
  stream_manager::stream_manager()
  {
  }

  stream_manager::~stream_manager()
  {
  }

  stream_ptr          stream_manager::create_stream(client &c, std::string name)
  {
    boost::mutex::scoped_lock l(m_mutex);

    if (!exists(name))
    {
      stream            *s = new stream(*this, c, name);
      stream_ptr        sp(s);

      m_streams[name] = sp;

      return sp;
    }
    else
      return stream_ptr();
  }

  void                stream_manager::delete_stream(std::string name)
  {
    boost::mutex::scoped_lock l(m_mutex);

    if (exists(name))
      m_streams.erase(name);
  }

  void                stream_manager::delete_stream(stream_ptr stream)
  {
    boost::mutex::scoped_lock l(m_mutex);
    stream_map::iterator iter;

    for (iter = m_streams.begin(); iter != m_streams.end(); iter++)
    {
      if (iter->second == stream)
      {
        m_streams.erase(iter);
        return;
      }
    }
  }

  stream_ptr          stream_manager::get_stream(std::string name)
  {
    boost::mutex::scoped_lock l(m_mutex);

    return m_streams[name];
  }

  stream_ptr          stream_manager::operator[](std::string name)
  {
    boost::mutex::scoped_lock l(m_mutex);

    return get_stream(name);
  }

  bool                stream_manager::exists(std::string name)
  {
    boost::mutex::scoped_lock l(m_mutex);

    return m_streams[name];
  }
}
