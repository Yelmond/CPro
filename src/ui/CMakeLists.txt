project( ui )

add_library( ui ui_widget.cpp )

find_package( fmt CONFIG REQUIRED )
target_link_libraries( ui PUBLIC fmt::fmt )
