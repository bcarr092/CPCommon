/*! \file   log.c
 
    \author Brent Carrara
 */
#include "log_functions.h"

static cpc_log_level g_current_log_level = CPC_LOG_LEVEL_TRACE;

cpc_error_code
cpc_log  (
          cpc_log_level in_log_level,
          CHAR*         in_file,
          INT32         in_line_number,
          CHAR*         in_log_format,
          ...
          )
{
  cpc_error_code error  = CPC_ERROR_CODE_NO_ERROR;
  FILE* handle          = stdout;
  
  va_list list;

  va_start( list, in_log_format );
  
  if( in_log_level == CPC_LOG_LEVEL_ERROR )
  {
    handle = stderr;
  }

  if( g_current_log_level <= in_log_level )
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

cpc_error_code
cpc_log_buffer_FLOAT64  (
                         cpc_log_level  in_log_level,
                         CHAR*          in_file,
                         INT32          in_line_number,
                         CHAR*          in_label,
                         FLOAT64*       in_buffer,
                         UINT32         in_buffer_length,
                         UINT32         in_num_columns
                         )
{
  cpc_error_code error  = CPC_ERROR_CODE_NO_ERROR;
  FILE* handle          = stdout;
  
  if( in_log_level == CPC_LOG_LEVEL_ERROR )
  {
    handle = stderr;
  }
  
  if( g_current_log_level <= in_log_level )
  {
    error = cpc_fprintf (
                         handle,
                         "%s %s:%s:%d[%s]%s (%p)\n",
                         __DATE__, __TIME__,
                         in_file, in_line_number,
                         cpc_log_level_to_string( in_log_level ),
                         in_label,
                         in_buffer
                         );
    
    if( CPC_ERROR_CODE_NO_ERROR != error )
    {
      if( NULL != in_buffer )
      {
        for( UINT32 i = 0; i < in_buffer_length; i++ )
        {
          if( i % in_num_columns == 0 )
          {
            if( i != 0 )
            {
              cpc_fprintf( handle, "\n" );
            }
            
            cpc_fprintf( handle, "0x%04x:\t", i );
          }
          
          cpc_fprintf( handle, "%+1.6e, ",  in_buffer[ i ] );
        }
      }
      
      error = cpc_fprintf( handle, "\n" );
    }
  }
  
  return( error );
}

cpc_error_code
cpc_log_buffer_FLOAT32  (
                         cpc_log_level  in_log_level,
                         CHAR*          in_file,
                         INT32          in_line_number,
                         CHAR*          in_label,
                         FLOAT32*       in_buffer,
                         UINT32         in_buffer_length,
                         UINT32         in_num_columns
                         )
{
  cpc_error_code error  = CPC_ERROR_CODE_NO_ERROR;
  FILE* handle          = stdout;
  
  if( in_log_level == CPC_LOG_LEVEL_ERROR )
  {
    handle = stderr;
  }
  
  if( g_current_log_level <= in_log_level )
  {
    error = cpc_fprintf (
                         handle,
                         "%s %s:%s:%d[%s]%s (%p)\n",
                         __DATE__, __TIME__,
                         in_file, in_line_number,
                         cpc_log_level_to_string( in_log_level ),
                         in_label,
                         in_buffer
                         );
    
    if( CPC_ERROR_CODE_NO_ERROR != error )
    {
      if( NULL != in_buffer )
      {
        for( UINT32 i = 0; i < in_buffer_length; i++ )
        {
          if( i % in_num_columns == 0 )
          {
            if( i != 0 )
            {
              cpc_fprintf( handle, "\n" );
            }
            
            cpc_fprintf( handle, "0x%04x:\t", i );
          }
          
          cpc_fprintf( handle, "%+1.6e, ",  in_buffer[ i ] );
        }
      }
      
      error = cpc_fprintf( handle, "\n" );
    }
  }
  
  return( error );
}

cpc_error_code
cpc_log_buffer  (
                 cpc_log_level  in_log_level,
                 CHAR*          in_file,
                 INT32          in_line_number,
                 CHAR*          in_label,
                 UCHAR*         in_buffer,
                 SSIZE          in_buffer_length,
                 UINT32         in_num_columns
                 )
{
  cpc_error_code error  = CPC_ERROR_CODE_NO_ERROR;
  FILE* handle          = stdout;
  
  if( in_log_level == CPC_LOG_LEVEL_ERROR )
  {
    handle = stderr;
  }
  
  if( g_current_log_level <= in_log_level )
  {
    error = cpc_fprintf (
                         handle,
                         "%s %s:%s:%d[%s]%s (%p)\n",
                         __DATE__, __TIME__,
                         in_file, in_line_number,
                         cpc_log_level_to_string( in_log_level ),
                         in_label,
                         in_buffer
                         );
    
    if( CPC_ERROR_CODE_NO_ERROR != error )
    {
      if( NULL != in_buffer )
      {
        for( UINT32 i = 0; i < in_buffer_length; i++ )
        {
          if( i % in_num_columns == 0 )
          {
            if( i != 0 )
            {
              cpc_fprintf( handle, "\n" );
            }
            
            cpc_fprintf( handle, "0x%04x:\t", i );
          }
          
          cpc_fprintf( handle, "0x%02x, ",  in_buffer[ i ] );
        }
      }
      
      error = cpc_fprintf( handle, "\n" );
    }
  }
  
  return( error );
}

cpc_error_code
cpc_log_set_log_level (
                       cpc_log_level in_new_log_level
                       )
{
  cpc_error_code error  = CPC_ERROR_CODE_NO_ERROR;
  
  if( in_new_log_level >= CPC_LOG_LEVEL_TRACE
      && in_new_log_level <= CPC_LOG_LEVEL_NO_LOGGING )
  {
    g_current_log_level = in_new_log_level;
  }
  else
  {
    error = CPC_ERROR_CODE_INVALID_LOG_LEVEL;
  }
  
  return( error );
}

cpc_log_level
cpc_log_get_current_log_level( void )
{
  return( g_current_log_level );
}

char*
cpc_log_level_to_string (
                         cpc_log_level in_log_level
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
