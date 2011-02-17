/*
** types.hh
** Login : <elthariel@rincevent>
** Started on  Wed Feb 16 16:01:01 2011 elthariel
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

#ifndef   	TYPES_HH_
# define   	TYPES_HH_

# include <string>
# include <vector>
# include <list>

# include <boost/asio.hpp>
# include <boost/asio/ssl.hpp>
# include <boost/signals2.hpp>
# include <boost/bind.hpp>
# include <boost/thread/mutex.hpp>

namespace e2
{
  namespace net
  {
    using boost::asio::ip::tcp;

    typedef boost::asio::ssl::stream<tcp::socket> ssl_socket;
  }
}


#endif	    /* !TYPES_HH_ */
