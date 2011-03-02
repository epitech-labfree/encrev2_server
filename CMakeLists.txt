cmake_minimum_required (VERSION 2.6)
project (e2_server)

set (e2_server_SOURCES types.hh
  main.cc
  server.cc
  connection.cc
  request.cc
  request_parser.cc
  stream_manager.cc
  stream.cc
  client.cc
  client_manager.cc
  e2.cc
  )

###############################################################3
# (ADD_PCH_RULE  _header_filename _src_list)
# Version 7/26/2010 4:55pm
#
# use this macro before "add_executable"
#
# _header_filename
#	header to make a .gch
#
# _src_list
#   the variable name (do not use ${..}) which contains a
#     a list of sources (a.cpp b.cpp c.cpp ...)
#  This macro will append a header file to it, then this src_list can be used in
#	"add_executable..."
#
#
# Now a .gch file should be generated and gcc should use it.
#       	(add -Winvalid-pch to the cpp flags to verify)
#
# make clean should delete the pch file
#
# example : ADD_PCH_RULE(headers.h myprog_SRCS)
MACRO (ADD_PCH_RULE  _header_filename _src_list)
	SET(_gch_filename "${_header_filename}.gch")
	LIST(APPEND ${_src_list} ${_gch_filename})
	SET (_args ${CMAKE_CXX_FLAGS})
	LIST(APPEND _args -c ${_header_filename} -o ${_gch_filename})
	GET_DIRECTORY_PROPERTY(DIRINC INCLUDE_DIRECTORIES)
	foreach (_inc ${DIRINC})
		LIST(APPEND _args "-I" ${_inc})
	endforeach(_inc ${DIRINC})
	SEPARATE_ARGUMENTS(_args)
	add_custom_command(OUTPUT ${_gch_filename}
		   COMMAND rm -f ${_gch_filename}
		   COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1} ${_args}
			    DEPENDS ${_header_filename})
ENDMACRO(ADD_PCH_RULE _header_filename _src_list)

##################################################################

find_package(PkgConfig REQUIRED)
pkg_check_modules(SSL REQUIRED libssl)
find_package(Boost 1.40 REQUIRED COMPONENTS thread system program_options regex)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SSL_INCLUDE_DIRS})

# Commented cause it seems to increase build time :-/
# add_pch_rule(types.hh e2_server_SOURCES)
add_executable(e2_server ${e2_server_SOURCES})
set_target_properties(e2_server PROPERTIES COMPILE_FLAGS "-g -O0 -Winvalid-pch")

target_link_libraries(e2_server ${Boost_LIBRARIES} ${SSL_LIBRARIES})


