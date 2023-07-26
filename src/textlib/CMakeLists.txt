project( textlib )

add_library( textlib textlib_kernel.cpp )

find_package( Freetype REQUIRED )
target_link_libraries( textlib PRIVATE Freetype::Freetype )

find_package( ICU REQUIRED COMPONENTS uc dt in io i18n data )
target_link_libraries( textlib PRIVATE ICU::uc ICU::dt ICU::in ICU::io ICU::i18n ICU::data )

find_package( harfbuzz REQUIRED )
target_link_libraries( textlib PRIVATE harfbuzz::harfbuzz )
