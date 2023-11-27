#ifdef WIN32
	#ifndef widget_EXPORT
		#define widget_EXPORTS __declspec( dllexport )
	#else
		#define widget_EXPORTS __declspec( dllimport )
	#endif
#else
	#define widget_EXPORTS __attribute__( ( visibility( "default" ) ) )
#endif

widget_EXPORTS void widgetise();
