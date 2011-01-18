#! /usr/bin/env ruby
## server.rb
## Login : <elthariel@rincevent>
## Started on  Tue Jan 18 12:55:55 2011 elthariel
## $Id$
##
## Author(s):
##  - elthariel <elthariel@gmail.com>
##
## Copyright (C) 2011 Epitech
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
##

ENCRE_SERVER_ROOT = File.dirname(File.expand_path(__FILE__))
$:.unshift ENCRE_SERVER_ROOT

puts "Encre Server root is : #{ENCRE_SERVER_ROOT}"

require 'encre_logger'
require 'stream_manager'
require 'settings'
require 'connection'

StreamManager::i

EventMachine::run {
  EventMachine::start_server Settings::i.address, Settings::i.port, ::Connection
  E2.logger.warn "Started Encre Server on #{Settings::i.address}:#{Settings::i.port}"
}

