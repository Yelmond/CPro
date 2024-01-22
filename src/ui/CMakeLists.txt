project( ui )

add_library( ui ui_widget.cpp  "ui_enums.h")

find_package( fmt CONFIG REQUIRED )
target_link_libraries( ui PRIVATE fmt::fmt )
