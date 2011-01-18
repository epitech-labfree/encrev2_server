##
## connection.rb
## Login : <elthariel@rincevent>
## Started on  Tue Jan 18 12:56:21 2011 elthariel
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

require 'rubygems'
require 'eventmachine'
require 'socket'
require 'client'
require 'protocol'

class Connection < EventMachine::Connection
  include E2::Protocol
  # @@states = [:connecting, :pushing, :getting]

  def post_init
    port, ip = Socket.unpack_sockaddr_in(get_peername)
    E2.logger.info "Client connecting from #{ip}:#{port}"

    @client = Client.new(self)
  end

  def receive_data data
    data_received(data)
    #port, ip = Socket.unpack_sockaddr_in(get_peername)
    #puts "Received #{data.length} bytes from #{ip}:#{port}"

    # if @state == :connecting
    #   if data =~ /PUT ([\w\/])/
    #     @state = :pushing
    #     @stream = $1
    #     send_data "OK\n"
    #     $treams[@stream] = Array.new
    #   elsif data =~ /GET ([\w\/])/ and $treams.has_key? $1
    #     @state = :getting
    #     @stream = $1
    #     send_data "OK\n"
    #     $treams[@stream].push self
    #   else
    #     send_data "NOK\n"
    #   end
    # elsif @state == :pushing
    #   $treams[@stream].each { |c| c.send_data data }
    # else
    #   port, ip = Socket.unpack_sockaddr_in(get_peername)
    #   puts "Received data from #{ip}:#{port} in reading mode :-/"
    # end
  end
end

