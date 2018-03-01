/**
 *       @file  sv_log.cpp
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

#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <stdarg.h>		// for va_list,etc
#include <libgen.h>
#include <stdio.h>		// for printf
#include <stdlib.h>		// for abort
#include <unistd.h>		// for getpid
#include <signal.h>		// for kill
#include <execinfo.h>	// for backtrace
#include <string.h>

#include "sv_log.h"

// these macros are defined in log4cplus/helpers/stringhelper.h
// shall be a mistake of log4cplus, everybody will use this macros, shalln't export
#undef PACKAGE
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#undef VERSION


using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

static Logger log_root		=  Logger::getRoot();


static int sv_logger_inited = 0;

static Logger * loggers[] =
{
	&log_root,
};

static int levels[] = {log4cplus::ALL_LOG_LEVEL, log4cplus::DEBUG_LOG_LEVEL, log4cplus::INFO_LOG_LEVEL, 
	log4cplus::WARN_LOG_LEVEL, log4cplus::ERROR_LOG_LEVEL, log4cplus::FATAL_LOG_LEVEL, log4cplus::OFF_LOG_LEVEL};

/**
 * @brief  init log module
 * @param  config_file : config file for log4cplus
 * @param  watch_time_sec : period time to reload config, in secs. 0 to disable reload
 * @return 0 when success
 */
//int sv_log_init(const char * config_file, int watch_time_sec);
int sv_log_init(const char * config_file, int watch_time_sec)
{
	static ConfigureAndWatchThread * config_thread = NULL;

	if ( !strncmp(config_file,"CONSOLE",7) )
	{
		// use printf
		printf("WARNING : use printf for log system\n");
		return 0;
	}

	if ( sv_logger_inited == 1 )
	{
		Logger::shutdown() ;
		if ( config_thread != NULL )
		{
			delete config_thread;
			config_thread = NULL;
		}
		sv_logger_inited = 0;
	}

	Logger root = Logger::getRoot();
	try 
	{
		if ( watch_time_sec > 0 )
		{
			if ( config_file )
			{
				config_thread = new ConfigureAndWatchThread(config_file, watch_time_sec * 1000);
				if ( config_thread == NULL )
					return -1;
			}
			else
			{
				return -1;
			}
		}
		else if ( config_file )
		{
			PropertyConfigurator::doConfigure(config_file);
		}
		else
		{
			BasicConfigurator config;
			config.configure();
		}
	}
	catch(...) {
		sv_logger_inited = 0;
		return -1;
	}
	sv_logger_inited = 1;
	return 0;
}

#ifdef __cplusplus 
extern "C" { 
#endif

/**
 * @brief  the log function
 * @param  logger : which logger module
 * @param  level : log level
 * @param  file : from file
 * @param  line : from line
 * @param  fmt : message format in printf format
 * @return none
 */
void sv_log_printf(unsigned int logger, unsigned int level, const char *filename,  int line, char *fmt, ...)
{

	va_list ap;
	char buf[2048] = {0};
    char file[1024] = {0};
    strcpy(file, filename);



	if(sv_logger_inited == 0)
	{
		va_start(ap, fmt);
		vprintf(fmt, ap);
		printf(" [%s:%d] ",file,line);
		printf("\n");
		va_end(ap);	
		return;
	}

	if(!loggers[logger]->isEnabledFor(levels[level]))
		return;

	va_start(ap, fmt);
	vsnprintf(buf,2048,fmt, ap);
	va_end(ap);
	loggers[logger]->forcedLog(levels[level],buf, basename(file), line);
}


/**
 * @brief  the assertion fail function
 * @param  str : the assertion expr string
 * @param  file : the file name
 * @param  line : the line no
 * @return none
 */
void sv_assert_fail(char *str, char *file, int line)
{
    const char *p = "Assertion \"%s\" failed at %s:%d!";
    SV_FATAL(const_cast <char *>(p), str , file, line);
	// raise a SIGINT, quit the program
	//	app_notice_agent("alarm", "internalerror", "runtimeerror", "critical", "sv_assert_fail");
	//raise(SIGINT);
	//sleep((unsigned int)10);
	abort();
}

#ifdef __cplusplus 
};
#endif
