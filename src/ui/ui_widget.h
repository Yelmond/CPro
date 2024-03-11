#pragma once

#include "ui_lib.h"
#include "ui_enums.h"
#include <vector>

namespace UI {
	template< typename T >
	class WidgetAllocator : public std::allocator< T > {
	public:
		template< typename U, typename... Args >
		void construct( U * p, Args &&... args ) {
			::new( reinterpret_cast< void * >( p ) ) U(
				std::forward< Args >( args )... );
		}

		template< typename U >
		struct rebind {
			using other = WidgetAllocator< U >;
		};
	};

	class Widget {
	private:
		ui_EXPORTS Widget();
		ui_EXPORTS explicit Widget( int num );
		ui_EXPORTS explicit Widget( float num );

	public:
		ui_EXPORTS Widget( const Widget & ) = delete;
		ui_EXPORTS Widget( Widget && );
		ui_EXPORTS ~Widget();

	private:
		template< typename... TArgs >
		Widget( Widget & parent, TArgs &&... args )
			: Widget( std::forward< TArgs >( args )... )
		{
			mParent = &parent;
		}

	public:
		Widget & addChild( Widget && widget );
		template< typename... TArgs > Widget & createChild( TArgs &&... args );

		Widget & getChild( int index );

		[[ nodiscard ]] size_t getChildCount() const;
		[[ nodiscard ]] int getField() const;

	private:
		using WidgetContainer = std::vector< Widget, WidgetAllocator< Widget > >;

		friend class Panel;
		friend class WidgetAllocator< Widget >;

		Widget * mParent;
		WidgetContainer mWidgets;

		int mField;
	};

	////

	inline Widget & Widget::addChild( Widget && widget ) {
		return mWidgets.emplace_back( *this, std::forward< Widget >( widget ) );
	}

	template< typename... TArgs >
	inline Widget & Widget::createChild( TArgs &&... args ) {
		return mWidgets.emplace_back( *this, std::forward< TArgs >( args )... );
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
