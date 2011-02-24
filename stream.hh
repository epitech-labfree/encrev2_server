/*
** stream.hh
** Login : <elthariel@rincevent>
** Started on  Thu Feb 24 05:49:34 2011 elthariel
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

#ifndef   	STREAM_HH_
# define   	STREAM_HH_

# include "types.hh"

namespace e2
{
  class client;
  typedef boost::shared_ptr<client>    client_ptr;
  class stream_manager;

  class stream : public boost::enable_shared_from_this<stream>,
                 private boost::noncopyable
  {
  public:
    void                        subscribe(client_ptr reader);
    bool                        unsubscribe(client_ptr reader);

  protected:
    stream(stream_manager &m, client &writer, std::string name);

    stream_manager              &m_streams;
    client                      &m_client;
    std::string                 m_name;
    boost::mutex                m_mutex; // for the list below
    std::list<client_ptr>       m_readers;

    friend                      class stream_manager;
  };

  typedef boost::shared_ptr<stream> stream_ptr;
}

#endif	    /* !STREAM_HH_ */
