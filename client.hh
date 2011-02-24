/*
** client.hh
** Login : <elthariel@rincevent>
** Started on  Thu Feb 24 05:24:56 2011 elthariel
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

#ifndef   	CLIENT_HH_
# define   	CLIENT_HH_

# include "types.hh"
# include "connection.hh"
# include "request_parser.hh"
# include "stream.hh"

namespace e2
{
  class client_manager;
  class stream_manager;

  class client : public net::receiver, public boost::enable_shared_from_this<client>,
                 private boost::noncopyable
  {
  public:
    enum type {UNKNOWN, WRITER, READER};

    ~client();

    bool                        receive_data(net::const_buffer_ptr data);
    bool                        send_data(net::const_buffer_ptr data);
    type                        type();
    stream_ptr                  stream();

  protected:
    client(stream_manager &sm, client_manager &cm, net::connection &c);

    stream_manager              &m_streams;
    client_manager              &m_clients;
    net::connection             &m_connnection;
    enum type                   m_type;
    stream_ptr                  m_stream;

    friend                      class client_manager;
  };

  typedef boost::shared_ptr<client>    client_ptr;
};


#endif	    /* !CLIENT_HH_ */
