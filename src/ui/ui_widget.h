#include "ui_lib.h"
#include "ui_enums.h"
#include <vector>

namespace UI {
	class Widget {
	public:
		ui_EXPORTS Widget( int num );
		ui_EXPORTS Widget( float num );
		ui_EXPORTS Widget( const Widget & ) = delete;
		ui_EXPORTS Widget( Widget && );
		ui_EXPORTS ~Widget();

	private:
		template< typename... TArgs >
		Widget( Widget & parent, TArgs &&... args )
			: Widget( std::forward< TArgs >( args )... )
			, mParent( &parent )
		{}

	public:
		Widget & addChild( Widget && widget );
		Widget & addChild( int num );
		Widget & getChild( int index );

		[[ nodiscard ]] size_t getChildCount() const;
		[[ nodiscard ]] int getField() const;

	private:
		Widget * mParent;
		std::vector< Widget > mWidgets;

		int mField;
	};

	////

	inline Widget & Widget::addChild( Widget && widget ) {
		return mWidgets.emplace_back( *this, std::forward< Widget >( widget ) );
	}

	inline Widget & Widget::addChild( int num ) {
		return mWidgets.emplace_back( *this, num );
	}

	inline Widget & Widget::getChild( int index ) {
		return mWidgets[ index ];
	}

	inline size_t Widget::getChildCount() const {
		return mWidgets.size();
	}

	inline int Widget::getField() const {
		return mField;
	}
}
