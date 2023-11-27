include_guard( GLOBAL )

macro ( init_cxx_modules )

	set( CMAKE_CXX_STANDARD 20 )

	# Enable C++ modules if the compiler supports them.
	#set( CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1 )

	# Set the module API version to the current version of CMake. This is required
	# to use the CMake module mode. This is a temporary workaround until the
	# module mode is the default.
	#if ( ${CMAKE_MINOR_VERSION} EQUAL 25 )
	#	set( CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "3c375311-a3c9-4396-a187-3227ef642046" )
	#elseif ( ${CMAKE_MINOR_VERSION} EQUAL 26 )
	#	set( CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a" )
	#else ()
	#	message( FATAL_ERROR "Unsupported CMake version." )
	#endif ()

	# Default to C++ extensions being off. Clang's modules support have trouble
	# with extensions right now and it is not required for any other compiler
	#set( CMAKE_CXX_EXTENSIONS OFF )

endmacro ()
