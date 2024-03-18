#pragma once

#include "ui_lib.h"
#include "ui_enums.h"
#include "fmt/core.h"
#include <vector>

namespace UI {
	class Widget;
	
	template< typename T >
	struct TypeNamePrinter {
		static const char * getName() {
			return "UNK";
		}
	};

	template<>
	struct TypeNamePrinter< int > {
		const char * getName() {
			return "int";
		}
	};
	template<>
	struct TypeNamePrinter< int & > {
		static const char * getName() {
			return "int&";
		}
	};
	template<>
	struct TypeNamePrinter< int && > {
		static const char * getName() {
			return "int&&";
		}
	};
	template<>
	struct TypeNamePrinter< Widget > {
		static const char * getName() {
			return "Widget";
		}
	};
	template<>
	struct TypeNamePrinter< Widget * > {
		static const char * getName() {
			return "Widget*";
		}
	};
	template<>
	struct TypeNamePrinter< Widget & > {
		static const char * getName() {
			return "Widget&";
		}
	};
	template<>
	struct TypeNamePrinter< Widget && > {
		static const char * getName() {
			return "Widget&&";
		}
	};

	template< typename T >
	class WidgetAllocator : public std::allocator< T > {
	public:
		template< typename U, typename... Args >
		void construct( U * p, Args &&... args ) {
			fmt::print( "construct() ARGS:" );
			( fmt::print( " {}", TypeNamePrinter< decltype( args ) >::getName() ), ... );
			fmt::print( "\n" );

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
		ui_EXPORTS explicit Widget( Widget && );
		ui_EXPORTS ~Widget();

		ui_EXPORTS Widget & operator=( Widget && );
		ui_EXPORTS bool operator==( const Widget & ) const;

	private:
		template< typename... TArgs >
		Widget( Widget & parent, TArgs &&... args )
			: Widget( std::forward< TArgs >( args )... )
		{
			fmt::print( "Adding parent {} to child {}\n", parent.getField(), mField );
			mParent = &parent;
		}

	public:
		Widget & addChild( Widget && widget );
		template< typename... TArgs > Widget & createChild( TArgs &&... args );

		bool deleteChild( Widget & widget );

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
		if ( widget.mParent == this )
			return widget;

		if ( widget.mParent == nullptr )
			return mWidgets.emplace_back( *this, std::forward< Widget >( widget ) );

		auto & otherParent = *widget.mParent;
		fmt::print( "addChild() from {} to {}\n", otherParent.getField(), mField );
		auto & newChild = mWidgets.emplace_back( *this, std::forward< Widget >( widget ) );
		otherParent.deleteChild( widget );
		return newChild;
	}

	template< typename... TArgs >
	inline Widget & Widget::createChild( TArgs &&... args ) {
		fmt::print( "createChild() ARGS:" );
		( fmt::print( " {}", args ), ... );
		fmt::print( "\n" );

		return mWidgets.emplace_back( *this, std::forward< TArgs >( args )... );
	}

	inline bool Widget::deleteChild( Widget & widget ) {
		auto it = std::find( mWidgets.begin(), mWidgets.end(), widget );
		if ( it == mWidgets.end() ) {
			return false;
		}

		mWidgets.erase( it );
		return true;
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
