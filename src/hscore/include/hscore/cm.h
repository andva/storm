#include <stdint.h>

#define HS_START_DEF() do {

#define HS_END_DEF() } while(false);

#define HS_DO_NOTHING HS_START_DEF(); HS_END_DEF();

#define HS_CACHE_LINE 32
#define HS_CACHE_ALIGN __declspec(align(HS_CACHE_LINE))

#define HS_DISSALLOW_COPY(__TypeName__) __TypeName__(const __TypeName__&) = delete
#define HS_DISSALLOW_ASSIGN(__TypeName__) void operator=(const __TypeName__&) = delete
#define HS_DISSALLOW_DEFAULT_CONSTRUCTOR(__TypeName__) __TypeName__() = delete

#define HS_DISSALLOW_COPY_ASSIGN(__TypeName__) \
	HS_DISSALLOW_COPY(__TypeName__); \
	HS_DISSALLOW_ASSIGN(__TypeName__);

#define HS_DISSALLOW_ALL_DEFAULTS(__TypeName__) \
	HS_DISSALLOW_COPY(__TypeName__); \
	HS_DISSALLOW_ASSIGN(__TypeName__); \
	HS_DISSALLOW_DEFAULT_CONSTRUCTOR(__TypeName__);
#ifndef HSCORE_CM_H
#define HSCORE_CM_H

#if defined(NDEBUG) && defined(__GNUC__)
#define U_ASSERT_ONLY __attribute__((unused))
#else
#define U_ASSERT_ONLY
#endif

#endif

#ifndef DISABLE_VC_WARNING
#if defined(_MSC_VER)
#define DISABLE_VC_WARNING(w)  \
						__pragma(warning(push))       \
						__pragma(warning(disable:w))
#else
#define DISABLE_VC_WARNING(w)
#endif
#endif

#ifndef RESTORE_VC_WARNING
#if defined(_MSC_VER)
#define RESTORE_VC_WARNING()   \
						__pragma(warning(pop))
#else
#define RESTORE_VC_WARNING()
#endif
#endif