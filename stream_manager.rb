##
## stream_manager.rb
## Login : <elthariel@rincevent>
## Started on  Tue Jan 18 12:33:11 2011 elthariel
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

require 'stream'
require 'singleton'

class StreamManager
  include Singleton

  def initialize
    @streams = Hash.new
  end

  def self.i
    StreamManager::instance
  end

  def [](name)
    @streams[name]
  end

  def exists?(name)
    @streams.has_key?(name)
  end

  def add(stream)
    unless exists?(stream.name)
      @streams[stream.name] = stream
    end
  end

  def remove(stream)
    if stream.kind_of?(String) && exists?(stream)
      @streams.delete stream
    elsif exists?(stream.name)
      @streams.delete stream.name
    end
  end

  alias :<< :add
  alias :>> :remove
end

