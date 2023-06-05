project( modlib )

add_library( modlib )

target_sources( modlib
	PUBLIC
		FILE_SET cxx_modules TYPE CXX_MODULES FILES modlib.cxx
)

find_package( fmt CONFIG REQUIRED )
target_link_libraries( modlib PRIVATE fmt::fmt )
