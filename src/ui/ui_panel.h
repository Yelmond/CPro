#pragma once

#include "ui_widget.h"

namespace UI {
	class Panel {
	public:
		Panel() = default;
		Panel( const Panel & ) = delete;
		Panel( Panel && ) = delete;
		~Panel() = default;

	public:
		[[ nodiscard ]] const Widget & rootWidget() const;
		[[ nodiscard ]] Widget & rootWidget();

		template< typename... TArgs >
		inline Widget & createChild( TArgs &&... args );

	private:
		Widget mRootWidget;
	};

	inline const Widget & Panel::rootWidget() const {
		return mRootWidget;
	}

	inline Widget & Panel::rootWidget() {
		return mRootWidget;
	}

	template< typename... TArgs >
	inline Widget & Panel::createChild( TArgs &&... args ) {
		return mRootWidget.createChild( std::forward< TArgs >( args )... );
	}
}