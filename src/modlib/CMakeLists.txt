project( modlib )

add_library( modlib )

target_sources( modlib
		PUBLIC
			modlib.cxx
)

find_package( fmt CONFIG REQUIRED )
target_link_libraries( modlib PRIVATE fmt::fmt )
