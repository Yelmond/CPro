#ifdef WIN32
	#ifndef textlib_EXPORT
		#define textlib_EXPORTS __declspec( dllexport )
	#else
		#define textlib_EXPORTS __declspec( dllimport )
	#endif
#else
	#define textlib_EXPORTS __attribute__( ( visibility( "default" ) ) )
#endif

textlib_EXPORTS void processText( const char * str );
