project( app )

add_executable( app app_main.cpp )

target_link_libraries( app PRIVATE modlib textlib )

# For each link library set on the app target, include its source directory as an include directory.
get_target_property( APP_LINK_LIBRARIES app LINK_LIBRARIES )
foreach( LINK_LIBRARY ${APP_LINK_LIBRARIES} )
	get_target_property( LINK_LIBRARY_SOURCE_DIR ${LINK_LIBRARY} SOURCE_DIR )
	target_include_directories( app PRIVATE ${LINK_LIBRARY_SOURCE_DIR} )
endforeach()
