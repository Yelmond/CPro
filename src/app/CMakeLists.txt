project( app )

add_executable( app app_main.cpp )

target_link_libraries( app PRIVATE modlib )
