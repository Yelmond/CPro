include_guard( GLOBAL )

macro ( init_cxx )

	set( CMAKE_CXX_STANDARD 23 )
	set( CMAKE_CXX_STANDARD_REQUIRED ON )
	set( CMAKE_CXX_EXTENSIONS OFF )

	# if ( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT WIN32 )
	# 	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++" )
	# endif ()

endmacro ()
