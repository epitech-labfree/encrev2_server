##
## stream.rb
## Login : <elthariel@rincevent>
## Started on  Tue Jan 18 12:34:13 2011 elthariel
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

class Stream
  attr_reader :name, :client, :subscribers

  def initialize(name, client)
    @name = name
    @client = client
    @subscribers = Array.new
  end

  def subscribe(client)
    @subscribers.push client unless @subscribers.include?(client)
  end
  def unsubscribe(client)
    @subscribers.delete(client)
  end

  alias :<< :subscribe
  alias :>> :unsubscribe

  def each_subscriber
    @subscribers.each { |s| yield s }
  end

  def data_pushed(data)
    @subscribers.each do |s|
      s.connection.send_data(data)
    end
  end

end

