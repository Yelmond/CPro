#include "ui_widget.h"
#include <fmt/format.h>

namespace UI {
	Widget::Widget() {
		fmt::print( "Widget created.\n" );
	}

	Widget::~Widget() {
		fmt::print( "Widget destroyed.\n" );
	}
}
