project( widget )

add_library( widget widget.cpp )

find_package( fmt CONFIG REQUIRED )
target_link_libraries( widget PRIVATE fmt::fmt )
