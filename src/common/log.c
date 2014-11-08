#include "log_functions.h"

CPC_LOG_LEVEL current_log_level = CPC_LOG_LEVEL_TRACE;

CPC_ERROR_CODE
cpc_log  (
          CPC_LOG_LEVEL in_log_level,
          CHAR*         in_file,
          INT32         in_line_number,
          CHAR*         in_log_format,
          ...
          )
{
  CPC_ERROR_CODE error  = CPC_ERROR_CODE_NO_ERROR;
  FILE* handle          = stdout;
  
  va_list list;

  va_start( list, in_log_format );
  
  if( in_log_level == CPC_LOG_LEVEL_ERROR )
  {
    handle = stderr;
  }

  if( current_log_level <= in_log_level )
  {
    error = cpc_fprintf (
                         handle,
                         "%s %s:%s:%d[%s]",
                         __DATE__, __TIME__,
                         in_file, in_line_number,
                         cpc_log_level_to_string( in_log_level )
                         );
    
    if( CPC_ERROR_CODE_NO_ERROR != error )
    {
      error = cpc_vfprintf( handle, in_log_format, list );
      
      if( CPC_ERROR_CODE_NO_ERROR != error )
      {
        error = cpc_fprintf( handle, "\n" );
      }
    }
  }

  va_end( list );

  return( error );
}

CPC_ERROR_CODE
cpc_log_set_log_level (
                       CPC_LOG_LEVEL in_new_log_level
                       )
{
  CPC_ERROR_CODE error  = CPC_ERROR_CODE_NO_ERROR;
  
  if( in_new_log_level >= CPC_LOG_LEVEL_TRACE
      && in_new_log_level <= CPC_LOG_LEVEL_NO_LOGGING )
  {
    current_log_level = in_new_log_level;
  }
  else
  {
    error = CPC_ERROR_CODE_INVALID_LOG_LEVEL;
  }
  
  return( error );
}

CPC_LOG_LEVEL
cpc_log_get_current_log_level( void )
{
  return( current_log_level );
}

char*
cpc_log_level_to_string (
                         CPC_LOG_LEVEL in_log_level
                         )
{
  switch( in_log_level )
  {
    case CPC_LOG_LEVEL_TRACE:
      return( CPC_LOG_LEVEL_TRACE_STRING );
    case CPC_LOG_LEVEL_DEBUG:
      return( CPC_LOG_LEVEL_DEBUG_STRING );
    case CPC_LOG_LEVEL_INFO:
      return( CPC_LOG_LEVEL_INFO_STRING );
    case CPC_LOG_LEVEL_WARN:
      return( CPC_LOG_LEVEL_WARN_STRING );
    case CPC_LOG_LEVEL_ERROR:
      return( CPC_LOG_LEVEL_ERROR_STRING );
    case CPC_LOG_LEVEL_NO_LOGGING:
      return( CPC_LOG_LEVEL_NO_STRING );
    default:
      return( NULL );
  }
}
