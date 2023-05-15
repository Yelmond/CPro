project( app )

add_executable( app app_main.cpp )

find_package( fmt CONFIG REQUIRED )
target_link_libraries( app PRIVATE fmt::fmt )
