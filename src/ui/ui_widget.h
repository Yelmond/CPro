#include "ui_lib.h"
#include "ui_enums.h"
#include <vector>

namespace UI {
	class Widget {
	public:
		ui_EXPORTS Widget( int num );
		ui_EXPORTS ~Widget();

	public:
		void addChild( Widget & widget );
		Widget & getChild( int index );

		[[ nodiscard ]] int getField() const;

	private:
		std::vector< Widget * > widgets;

		int field;
	};

	////

	inline void Widget::addChild( Widget & widget ) {
		widgets.emplace_back( &widget );
	}

	inline Widget & Widget::getChild( int index ) {
		return *widgets[ index ];
	}

	inline int Widget::getField() const {
		return field;
	}
}
