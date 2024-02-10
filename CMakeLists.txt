cmake_minimum_required( VERSION 3.27 )

enable_testing()

include( init )
init()

project( CPro VERSION 1.0 LANGUAGES CXX )

add_subdirectory( src )
add_subdirectory( test )
