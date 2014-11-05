/*! \file   log.h
    \brief  Logging function that allows for messages to be logged at multiple
            different logging levels.
 */
#ifndef __LOG_H__
#define __LOG_H__

#include "cpcommon.h"
#include "error_codes.h"

#define CPC_LOG_LEVEL_TRACE_STRING  "TRACE"
#define CPC_LOG_LEVEL_DEBUG_STRING  "DEBUG"
#define CPC_LOG_LEVEL_INFO_STRING   "INFO"
#define CPC_LOG_LEVEL_WARN_STRING   "WARN"
#define CPC_LOG_LEVEL_ERROR_STRING  "ERROR"

/*! \def    CPC_LOG_STRING
    \brief  Logging function for strings. Used to log static messages.
 */
#define CPC_LOG_STRING( in_log_level, in_string ) \
          cpc_log( in_log_level, __FILE__, __LINE__, in_string )

/*! \def    CPC_LOG
    \brief  Logging for function that provides a printf-like interface. This is
            the logging function that should be called as it will preserve the
            file and line number the log function call is made from.
 */
#define CPC_LOG( in_log_level, in_log_format, ... ) \
          cpc_log( in_log_level, __FILE__, __LINE__, in_log_format, __VA_ARGS__ )

/*! \enum   cpc_log_levels
    \brief  The supported log levels. Trace is the lowest (0), error is the
            highest (4). When the log level is set only CPC_LOG calls with
            a log level equal to or above the current log level will be
            printed.
 */
enum cpc_log_levels
{
  CPC_LOG_LEVEL_TRACE = 0,
  CPC_LOG_LEVEL_DEBUG,
  CPC_LOG_LEVEL_INFO,
  CPC_LOG_LEVEL_WARN,
  CPC_LOG_LEVEL_ERROR
};

/*! \var    CPC_LOG_LEVEL
    \brief  A type definition for the log level.
 */
typedef INT32 CPC_LOG_LEVEL;

/*! \fn     CPC_ERROR_CODE cpc_log  (
              CPC_LOG_LEVEL in_log_level,
              CHAR*         in_file,
              INT32         in_line_number,
              CHAR*         in_log_format,
              ...
            )
    \brief  Logging function that will either not output the log (if
            in_log_level is below the current log level) or output the log
            to either stdout or stderr (if in_log_level is the ERROR level).
 
    \param  in_log_level    The log level the message should be logged at
    \param  in_file         The file name cpc_log was called from
    \param  in_line_number  The line number cpc_log was called on
    \param  in_log_format   The printf formatted format string
    \param  ...             The variable length argument list to use in 
                            formatting the log.
    \return Either CPC_ERROR_CODE_NO_ERROR if no error is detected or an error.
 */
CPC_ERROR_CODE
cpc_log  (
          CPC_LOG_LEVEL in_log_level,
          CHAR*         in_file,
          INT32         in_line_number,
          CHAR*         in_log_format,
          ...
          );

/*! \fn     CPC_ERROR_CODE cpc_log_set_log_level (
              CPC_LOG_LEVEL in_new_log_level
            )
    \brief  Set the current log level to in_new_log_level
 
    \param  in_new_log_level  The log level to set the current log level to
    \return Either CPC_ERROR_CODE_NO_ERROR if the current log level is changed
            or an error code.
 */
CPC_ERROR_CODE
cpc_log_set_log_level (
                       CPC_LOG_LEVEL in_new_log_level
                       );

/*! \fn     cpc_log_get_current_log_level
    \brief  Provides access to the currently configured log level
    
    \return Returns the currently configured log level
 */
CPC_LOG_LEVEL
cpc_log_get_current_log_level( void );

/*! \fn     CHAR* cpc_log_level_to_string( CPC_LOG_LEVEL in_log_level )
    \brief  Translates the log level to its string representation
 
    \param  in_log_level  The log level to translate to a string.
    \return String representation of the given log level
 */
char*
cpc_log_level_to_string (
                         CPC_LOG_LEVEL in_log_level
                         );

#endif /* __LOG_H__ */
