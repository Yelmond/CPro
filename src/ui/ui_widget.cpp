#include "ui_widget.h"
#include <fmt/format.h>

namespace UI {
	Widget::Widget()
		: mParent( nullptr )
		, mField( 0 )
	{
		fmt::print( "Widget(): {}\n", mField );
	}

	Widget::Widget( int num )
		: mParent( nullptr )
		, mField( num )
	{
		fmt::print( "Widget( int num ): {}\n", mField );
	}

	Widget::Widget( float num )
		: mParent( nullptr )
		, mField( static_cast< int >( num ) )
	{
		fmt::print( "Widget( float num ): {}\n", mField );
	}

	Widget::Widget( Widget && other )
		: mParent( other.mParent )
		, mWidgets( std::move( other.mWidgets ) )
		, mField( other.mField )
	{
		other.mParent = nullptr;
		other.mField = 0;
		fmt::print( "Widget( Widget && other ): {}\n", mField );
	}

	Widget::~Widget() {
		fmt::print( "~Widget(): {}\n", mField );
	}

	Widget & Widget::operator=( Widget && other ) {
		if ( this != &other ) {
			mParent = other.mParent;
			mWidgets = std::move( other.mWidgets );
			mField = other.mField;

			other.mParent = nullptr;
			other.mField = 0;
		}

		fmt::print( "Widget & operator=( Widget && other ): {}\n", mField );

		return *this;
	}

	bool Widget::operator==( const Widget & other ) const {
		return this == &other;
	}
}
