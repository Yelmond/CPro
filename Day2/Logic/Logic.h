#ifdef _MSC_VER
	#ifdef Logic_EXPORTS
		#define LIB_LOGIC __declspec( dllexport )
	#else
		#define LIB_LOGIC __declspec( dllimport )
	#endif
#else
	#define LIB_LOGIC __attribute__( ( visibility( "default" ) ) )
#endif


