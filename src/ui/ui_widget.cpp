#include "ui_widget.h"
#include <fmt/format.h>

namespace UI {
	Widget::Widget( int num )
		: field( num )
	{
		fmt::print( "Widget created.\n" );
	}

	Widget::~Widget() {
		fmt::print( "Widget destroyed.\n" );
	}
}
