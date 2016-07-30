#include <hscore/log.h>

#define LOG_GR "GRFX"
#undef LOG_WARNING
#define LOG_WARNING(...) LOG_WARNING_I(LOG_GR, ##__VA_ARGS__)
#undef LOG_DEBUG
#define LOG_DEBUG(...) LOG_DEBUG_I(LOG_GR, ##__VA_ARGS__)
#undef LOG_INFO
#define LOG_INFO(...) LOG_INFO_I(LOG_GR, ##__VA_ARGS__)
#undef LOG_ERROR
#define LOG_ERROR(...) LOG_ERROR_I(LOG_GR, ##__VA_ARGS__)