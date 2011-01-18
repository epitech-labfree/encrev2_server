##
## encre_logger.rb
## Login : <elthariel@rincevent>
## Started on  Tue Jan 18 13:09:09 2011 elthariel
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

require 'logger'

module E2
  begin
    if ['STDOUT', 'STDERR'].include?(Settings::i.logfile)
      @@_logger = Logger.new(Kernel.const_get(Settings::i.logfile.to_sym))
    else
      @@_logger = Logger.new(Settings::i.logfile)
    end
    @@_logger.level = Logger.const_get(Settings::i.loglevel.to_sym)
  rescue
    @@_logger = Logger.new(STDERR)
    @@_logger.level = Logger::DEBUG
  end
  @@_logger.progname = "E2Server"

  def self.logger
    @@_logger
  end
end
