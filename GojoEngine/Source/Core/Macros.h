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
// Unsigned types
// ================================================================================
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

// ================================================================================
// Signed types
// ================================================================================
using s8 = signed char;
using s16 = signed short;
using s32 = signed int;
using s64 = signed long long;

// ================================================================================
// Floating point types
// ================================================================================
using f32 = float;
using f64 = double;

// ================================================================================
// Boolean types
// ================================================================================
using b8 = bool;

#define TRUE 1
#define FALSE 0

// ================================================================================
// Static Assertions
// ================================================================================
#define GOJO_STATIC_ASSERT static_assert

// Ensure correct size on different platforms
GOJO_STATIC_ASSERT(sizeof(u8) == 1, "u8 expected to be 1 byte.");
GOJO_STATIC_ASSERT(sizeof(u16) == 2, "u16 expected to be 2 bytes.");
GOJO_STATIC_ASSERT(sizeof(u32) == 4, "u32 expected to be 4 bytes.");
GOJO_STATIC_ASSERT(sizeof(u64) == 8, "u64 expected to be 8 bytes.");

GOJO_STATIC_ASSERT(sizeof(s8) == 1, "s8 expected to be 1 byte.");
GOJO_STATIC_ASSERT(sizeof(s16) == 2, "s16 expected to be 2 bytes.");
GOJO_STATIC_ASSERT(sizeof(s32) == 4, "s32 expected to be 4 bytes.");
GOJO_STATIC_ASSERT(sizeof(s64) == 8, "s64 expected to be 8 bytes.");

GOJO_STATIC_ASSERT(sizeof(f32) == 4, "f32 expected to be 4 bytes.");
GOJO_STATIC_ASSERT(sizeof(f64) == 8, "f64 expected to be 8 bytes.");
GOJO_STATIC_ASSERT(sizeof(b8) == 1, "b8 expected to be 1 byte.");

// ================================================================================
// Assertions
// ================================================================================
#define GojoDebugBreak() __debugbreak()

#ifdef GOJO_ASSERTIONS_ENABLED
	// Define Assertions

#define GOJO_ASSERT(expr)										   \
	{                                                              \
		if (expr) {}                                               \
		else                                                       \
		{                                                          \
			GOJO_LOG_ASSERT(expr, "", __FILE__, __LINE__);         \
			GojoDebugBreak();                                      \
		}                                                          \
	}

#define GOJO_ASSERT_MESSAGE(expr, message)						   \
	{                                                              \
		if (expr) {}                                               \
		else                                                       \
		{                                                          \
			GOJO_LOG_ASSERT(expr, message, __FILE__, __LINE__);    \
			GojoDebugBreak();                                      \
		}                                                          \
	}

#ifdef GOJO_DEBUG_BUILD
#define GOJO_ASSERT_DEBUG(expr)									   \
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