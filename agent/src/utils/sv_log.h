/**
 *       @file  sv_log.h
 *      @brief  log for sv platform
 *
 * Detailed description starts here.
 *
 *     @author  raymond (), raymond@fonsview.com
 *
 *   @internal
 *     Created  2008-4-17
 *    Revision  ---
 *    Compiler  gcc/g++
 *     Company  fonsview Co. Ltd.
 *   Copyright  Copyright (c) 2008, raymond
 *
 * =====================================================================================
 */

#ifndef __SV_LOG_H__
#define __SV_LOG_H__

extern int sv_log_init(const char *config_file, int watch_time_sec);
#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>

enum {
	SV_LOG_LVL_DBG   = 1,
	SV_LOG_LVL_INFO  = 2,
	SV_LOG_LVL_WARN  = 3,
	SV_LOG_LVL_ERROR = 4,
	SV_LOG_LVL_FATAL = 5,
	SV_LOG_LVL_OFF   = 6
};
enum
{
    LOGGER_DEFAULT = 0,
};

extern void sv_log_printf(unsigned int logger, unsigned int level, const char *filename,  int line, char *fmt, ...);

#define SV_LOG_LVL_LOG SV_LOG_LVL_DBG
#define SV_ASSERT(a)	{ if ( !(a) ) sv_assert_fail(#a, __FILE__, __LINE__); }
#define SV_LOG(s, ...)  sv_log_printf(LOGGER_DEFAULT, SV_LOG_LVL_LOG, __FILE__, __LINE__, s, ##__VA_ARGS__)
#define SV_DEBUG(s, ...)  sv_log_printf(LOGGER_DEFAULT, SV_LOG_LVL_DBG, __FILE__, __LINE__, s, ##__VA_ARGS__)
#define SV_INFO(s, ...)  sv_log_printf(LOGGER_DEFAULT, SV_LOG_LVL_INFO, __FILE__, __LINE__, s, ##__VA_ARGS__)
#define SV_WARN(s, ...)  sv_log_printf(LOGGER_DEFAULT, SV_LOG_LVL_WARN, __FILE__, __LINE__, s, ##__VA_ARGS__)
#define SV_ERROR(s, ...)  sv_log_printf(LOGGER_DEFAULT, SV_LOG_LVL_ERROR, __FILE__, __LINE__, s, ##__VA_ARGS__)
#define SV_FATAL(s, ...)  sv_log_printf(LOGGER_DEFAULT, SV_LOG_LVL_ERROR, __FILE__, __LINE__, s, ##__VA_ARGS__)
#ifdef __cplusplus
};
#endif


#endif /* __SV_LOG_H__ */
