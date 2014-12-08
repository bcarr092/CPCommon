/*! \file log_definitions.h
    \brief  This file contains the definitions for the logger. All constants
            and typedefs have been placed in this file since they are used by
            both log_functions.h and cpcommon.h.
 */
#ifndef _LOG_DEFINITIONS_H__
#define _LOG_DEFINITIONS_H__

#define CPC_LOG_LEVEL_TRACE_STRING  "TRACE"
#define CPC_LOG_LEVEL_DEBUG_STRING  "DEBUG"
#define CPC_LOG_LEVEL_INFO_STRING   "INFO"
#define CPC_LOG_LEVEL_WARN_STRING   "WARN"
#define CPC_LOG_LEVEL_ERROR_STRING  "ERROR"
#define CPC_LOG_LEVEL_NO_STRING     "Disabled"

/*! \enum   cpc_log_levels
    \brief  The supported log levels. Trace is the lowest (0), error is the
            highest (4). When the log level is set only CPC_LOG calls with
            a log level equal to or above the current log level will be
            printed. NO_LOGGING is used to disable logging (usually for tests).
 */
enum cpc_log_levels
{
  CPC_LOG_LEVEL_TRACE       = 0,
  CPC_LOG_LEVEL_DEBUG,
  CPC_LOG_LEVEL_INFO,
  CPC_LOG_LEVEL_WARN,
  CPC_LOG_LEVEL_ERROR,
  CPC_LOG_LEVEL_NO_LOGGING
};

/*! \var    cpc_log_level
    \brief  A type definition for the log level.
 */
typedef INT32 cpc_log_level;

#endif  /*  _LOG_DEFINITIONS_H__  */
