##
## settings.rb
## Login : <elthariel@rincevent>
## Started on  Tue Jan 18 13:01:09 2011 elthariel
## $Id$
##
## Author(s):
##  - elthariel <elthariel@gmail.com>
##
## Copyright (C) 2011 elthariel
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

require 'singleton'
require 'fileutils'
require 'yaml'

class Settings
  include Singleton

  def self.i
    self.instance
  end

  def initialize()
    @cfg_path = ENCRE_SERVER_ROOT + '/settings.yml'
    @data = Hash.new

    defaults
    if !File.exists? @cfg_path
      save
    end
    load
  end

  def defaults
    @data['version'] = 0
    @data['logfile'] = 'STDERR'
    @data['loglevel'] = 'DEBUG'
    @data['address'] = '0.0.0.0'
    @data['port'] = 4242
  end

  def save
    serialized_data = @data.to_yaml
    f = File.new(@cfg_path, "w")
    f.write(serialized_data)
    f.close
  end

  def load
    if File.readable? @cfg_path
      loaded = YAML.load_file(@cfg_path)
      @data.merge! loaded
    end
    apply

    puts "----------------------"
    puts "Dumping Encre Server Settings"
    puts @data
    puts "----------------------"
  end

  def method_missing(sym, *args)
    if (sym.to_s =~ /=\Z/)
      var_name = sym.to_s.gsub('=','')
      @data[var_name] = args[0]
    else
      @data[sym.to_s]
    end
  end
end

