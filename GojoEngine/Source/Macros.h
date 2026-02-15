#pragma once

#ifdef GOJOENGINE_EXPORTS
	#define GOJO_API __declspec(dllexport)
#else
	#define GOJO_API __declspec(dllimport)
#endif