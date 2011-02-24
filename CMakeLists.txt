cmake_minimum_required (VERSION 2.6)
project (e2_server)

set (e2_server_SOURCES main.cc
  server.cc
  connection.cc
  e2.cc
  )

find_package(PkgConfig REQUIRED)
pkg_check_modules(SSL REQUIRED libssl)
find_package(Boost 1.40 REQUIRED COMPONENTS thread system program_options)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SSL_INCLUDE_DIRS})

add_executable(e2_server ${e2_server_SOURCES})

target_link_libraries(e2_server ${Boost_LIBRARIES} ${SSL_LIBRARIES})


