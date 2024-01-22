cmake_minimum_required( VERSION 3.27 )

enable_testing()

include( init )

set( CMAKE_CXX_STANDARD 20 )

project( CPro VERSION 1.0 LANGUAGES CXX )

add_subdirectory( src )
add_subdirectory( test )
