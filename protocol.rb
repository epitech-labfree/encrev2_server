##
## protocol.rb
## Login : <elthariel@rincevent>
## Started on  Tue Jan 18 12:32:40 2011 elthariel
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

module E2
  module Protocol
    def initialize()
      @buffer = String.new
    end

    def end_of_request?
      return @buffer =~ /\n\n/
    end

    def request_ok!
      send_data "OK\n\n"
    end
    def request_nok!
      send_data "NOK\n\n"
      close_connection_after_writing
    end

    def publish(stream_name)
      E2.logger.debug "Client is publishing #{stream_name}"
      StreamManager::i << (Stream.new(stream_name, @client))
      @client.stream = stream_name
      @client.state = :publishing
    end

    def read(stream_name)
      E2.logger.debug "Client is reading #{stream_name}"
      @client.stream = stream_name
      @client.state = :reading
      StreamManager::i[stream_name] << @client
    end

    def parse_request
      res = true

      if @buffer =~ /PUT ([\w\/\.]+)\n/ && !StreamManager::i.exists?($1)
        publish($1)
      elsif @buffer =~ /GET ([\w\/\.]+)\n/ && StreamManager::i.exists?($1)
        read($1)
      else
        res = false
      end

      @buffer = String.new
      res
    end

    def data_received(data)
      if @client.state == :connecting
        @buffer << data
        if end_of_request?
          if parse_request
            request_ok!
          else
            request_nok!
          end
        end
      elsif @client.state == :publishing
        StreamManager::i[@client.stream].data_pushed(data)
      else
        E2.logger.warn "A client is pushing data but he's not a publisher nor connecting"
      end
    end
  end
end
