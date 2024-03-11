#include <ui.h>
#include <iostream>

int main() {
	UI::Panel panel;

	auto & widget42 = panel.createChild( 42 );
	std::printf( "Widget created: %d\n", widget42.getField() );

	return 0;
}
