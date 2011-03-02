/*
** request_parser.cc
** Login : <elthariel@rincevent>
** Started on  Thu Feb 24 17:39:30 2011 elthariel
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
#include <boost/regex.hpp>
#include "request_parser.hh"

using namespace std;

namespace e2
{
  request_parser::request_parser()
  {
  }

  bool                request_parser::feed(net::const_buffer_ptr data)
  {
    m_raw_request.append(data->begin(), data->end());

    if (has_end_token())
    {
      fill_request();
      return true;
    }
    else
      return false;
  }

  bool                request_parser::is_complete()
  {
    return has_end_token() && m_request.is_valid();
  }

  request_parser::operator bool()
  {
    return is_complete();
  }

  request             &request_parser::get_request()
  {
    return m_request;
  }

  bool                request_parser::has_end_token()
  {
    boost::regex      end_token("\n\n\n");

    return regex_search(m_raw_request, end_token);
  }

  bool                request_parser::fill_request()
  {
    std::cout << "request_parser::fill_request()" << std::endl;
    ///std::cout << m_raw_request << std::endl;

    std::string       r;
    std::string       action;
    std::string       stream;
    boost::smatch     match;

    boost::regex      extract_re("(.+)\n\n");
    //boost::regex      action_re("(PUT|GET) ([[:word:]]+)(.*)");
    boost::regex      action_re("(PUT|GET)");

    regex_match(m_raw_request, match, extract_re, boost::match_continuous);
    r = match[1];
    cout << "request is" << endl << r << endl;
    match = boost::smatch();
    if (!regex_match(r, match, action_re))
      cout << "can't find action" << endl;

    for (uint32_t i = 0; i < match.size(); i++)
      std::cout << "Match result " << i << " is:" << std::endl
                << match[i] << std::endl;

    return m_request.is_valid();
  }
}
