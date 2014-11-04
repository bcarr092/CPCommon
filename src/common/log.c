#include "log.h"

CPC_LOG_LEVEL current_log_level = CPC_LOG_LEVEL_DEBUG;

CPC_ERROR_CODE
  cpc_log  (
              CPC_LOG_LEVEL in_log_level,
              CHAR*         in_log_format,
              ...
           )
{
  CPC_ERROR_CODE error   = CPC_ERROR_CODE_NO_ERROR;
  va_list list;

  va_start( list, in_log_format );

  if( current_log_level <= in_log_level )
  {
    if( in_log_level == CPC_LOG_LEVEL_ERROR )
    {
      error = cpc_vfprintf( stderr, in_log_format, list );
    }
    else
    {
      error = cpc_vprintf( in_log_format, list );
    }
  }

  va_end( list );

  return( error );
}

void
  cpc_log_set_log_level (
                          CPC_LOG_LEVEL in_new_log_level
                        )
{
  if( in_new_log_level >= CPC_LOG_LEVEL_TRACE
      && in_new_log_level <= CPC_LOG_LEVEL_ERROR )
  {
    current_log_level = in_new_log_level;
  }
}

