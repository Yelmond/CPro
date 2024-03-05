#pragma once

#ifdef _WIN32
	#ifndef ui_EXPORT
		#define ui_EXPORTS __declspec( dllexport )
	#else
		#define ui_EXPORTS __declspec( dllimport )
	#endif
#else
	#define ui_EXPORTS __attribute__( ( visibility( "default" ) ) )
#endif
