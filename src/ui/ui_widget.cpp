#include "ui_widget.h"
#include <fmt/format.h>

namespace UI {
	Widget::Widget()
		: mParent( nullptr )
		, mField( 0 )
	{
		fmt::print( "Widget created.\n" );
	}

	Widget::Widget( int num )
		: mParent( nullptr )
		, mField( num )
	{
		fmt::print( "Widget created.\n" );
	}

	Widget::Widget( float num )
		: mParent( nullptr )
		, mField( static_cast< int >( num ) )
	{
		fmt::print( "Widget created.\n" );
	}

	Widget::Widget( Widget && other )
		: mParent( other.mParent )
		, mWidgets( std::move( other.mWidgets ) )
		, mField( other.mField )
	{
		other.mParent = nullptr;
		other.mField = 0;
		fmt::print( "Widget moved.\n" );
	}

	Widget::~Widget() {
		fmt::print( "Widget destroyed.\n" );
	}
}
