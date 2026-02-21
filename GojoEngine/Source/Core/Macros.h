#pragma once

#include <cassert>

// ================================================================================
// Platform Detection
// ================================================================================
#if defined(_WINDOWS)
#define GOJO_PLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit Windows required for GojoEngine"
#endif
#else
#error "Unknown platform!"
#endif

// ================================================================================
// DLL Export/Import
// ================================================================================
#ifdef GOJOENGINE_EXPORTS
#define GOJO_API __declspec(dllexport)
#else
#define GOJO_API __declspec(dllimport)
#endif

// ================================================================================
// Static Assertions Helpers
// ================================================================================
#define GOJO_STATIC_ASSERT(expr, message) \
    static_assert(expr, "Static assert failed: " message)

#define GOJO_RUNTIME_ASSERT(expr, message) \
	assert((expr) && (message))

// ================================================================================
// Assertions
// ================================================================================
#define GojoDebugBreak() __debugbreak()

#ifdef GOJO_ASSERTIONS_ENABLED
	// Define Assertions

#define GOJO_ASSERT(expr)											   \
		{                                                              \
			if (expr) {}                                               \
			else                                                       \
			{                                                          \
				GOJO_LOG_ASSERT(expr, "", __FILE__, __LINE__);         \
				GojoDebugBreak();                                      \
			}                                                          \
		}

#define GOJO_ASSERT_MESSAGE(expr, message)						       \
		{                                                              \
			if (expr) {}                                               \
			else                                                       \
			{                                                          \
				GOJO_LOG_ASSERT(expr, message, __FILE__, __LINE__);    \
				GojoDebugBreak();                                      \
			}                                                          \
		}

#ifdef GOJO_DEBUG_BUILD
#define GOJO_ASSERT_DEBUG(expr)									       \
			{                                                          \
				if (expr) {}                                           \
				else                                                   \
				{                                                      \
					GOJO_LOG_ASSERT(expr, "", __FILE__, __LINE__);     \
					GojoDebugBreak();                                  \
				}                                                      \
			}
#else
#define GOJO_ASSERT_DEBUG(expr) // disable in non-debug mode
#endif

#else
	// Empty define (Assertions Disabled)
#define GOJO_ASSERT(expr)
#define GOJO_ASSERT_MESSAGE(expr, message)
#define GOJO_ASSERT_DEBUG(expr)
#endif