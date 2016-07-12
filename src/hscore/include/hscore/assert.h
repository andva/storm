#ifndef HSCORE_ASSERT_H
#define HSCORE_ASSERT_H

#include <hscore/log.h>
#include <hscore/debug/break.h>
#include <hscore/cm.h>
#pragma once

#define HS_BREAK_ASSERT

namespace hscore
{

	inline void hsAssertionFailed(const char * const conditionString, const char * const file, int32_t line)
	{
		hscore::logText(hscore::Logger::Error, "ASSERT", file, line, "`%s` failed", conditionString);
#ifdef HS_BREAK_ASSERT
		hsDebugBreak();
#endif
	}
} // namespace hailstorm


///////////////////////////////////////////////////////////////////////////////
/// ANALYSIS_ASSUME
///
///
/// Example usage:
///    char Function(char* p) {
///       EA_ANALYSIS_ASSUME(p != NULL);
///       return *p;
///    }
///
#if !defined(ANALYSIS_ASSUME)
#if defined(_MSC_VER) && (_MSC_VER >= 1300) && !defined(CS_UNDEFINED_STRING)
#define ANALYSIS_ASSUME(x) __analysis_assume(x)
#else
#define ANALYSIS_ASSUME(x)
#endif
#endif

#endif
#define HS_ASSERT(expression) \
	DISABLE_VC_WARNING(4127) \
	do { \
		ANALYSIS_ASSUME(expression); \
		(void)((expression) || (hscore::hsAssertionFailed(#expression, __FILE__, __LINE__), 0)); \
	} while (0) \
	RESTORE_VC_WARNING()