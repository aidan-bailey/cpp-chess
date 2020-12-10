cmake_minimum_required( VERSION 3.2 )

project ( cpp-chess )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

file( GLOB SRCS src/main.cc src/models/*.cc )

include_directories( include src/models src/enums )

add_executable( cpp-chess ${SRCS} )
