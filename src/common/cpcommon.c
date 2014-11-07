#include "cpcommon.h"

INT32
cpc_snprintf  (
               CHAR**        io_string,
               USIZE         in_string_length,
               const CHAR*   in_string_format,
               ...
               )
{
  va_list list;
  
  va_start( list, in_string_format );
  
  *io_string = ( CHAR * ) malloc( sizeof( CHAR ) * in_string_length );
    
  memset( *io_string, 0x0, ( in_string_length + 1 ) );
  
  INT32 return_value =
    CPC_VSNPRINTF( *io_string, in_string_length, in_string_format, list );
  
  va_end( list );
  
  return( return_value );
}

INT32
cpc_printf  (
             const CHAR* in_string_format,
             ...
             )
{
  va_list list;
  
  va_start( list, in_string_format );
  
  INT32 return_value = CPC_VPRINTF( in_string_format, list );
  
  va_end( list );
  
  return( return_value );
}

INT32
cpc_vprintf  (
              const CHAR* in_string_format,
              va_list     in_list
              )
{
  INT32 return_value =
      CPC_VPRINTF( in_string_format, in_list );

  return( return_value );
}

INT32
cpc_fprintf (
             FILE* in_handle,
             const CHAR* in_string_format,
             ...
             )
{
  va_list list;
  
  va_start( list, in_string_format );
  
  INT32 return_value = CPC_VFPRINTF( in_handle, in_string_format, list );
  
  va_end( list );
  
  return( return_value );
}

INT32
cpc_vfprintf (
              FILE*       in_handle,
              const CHAR* in_string_format,
              va_list     in_list
              )
{
  INT32 return_value =
      CPC_VFPRINTF( in_handle, in_string_format, in_list );

  return( return_value );
}

CHAR*
cpc_convert_code_to_cstring  (
                              UINT32 in_code
                              )
{
  CHAR* code = NULL;
  
  if( noErr != in_code )
  {
    code = ( CHAR* ) malloc( CPC_CODE_STRING_LENGTH * sizeof( CHAR ) );
    
    memset( code, 0, CPC_CODE_STRING_LENGTH * sizeof( CHAR ) );
    
    * ( UINT32 * ) ( code + 1 ) = CFSwapInt32HostToBig( in_code );
    
    if( isprint( code[ 1 ] ) && isprint( code[ 2 ] )
       && isprint( code[ 3 ] ) && isprint( code[ 4 ] ) )
    {
      code[ 0 ] = code[ 5 ] = '\'';
      code[ 6 ] = '\0';
    }
  }
  
  return( code );
}

void
cpc_print_code (
                CPC_LOG_LEVEL  in_log_level,
                CHAR*          in_file,
                INT32          in_line_number,
                OSStatus       in_code
                )
{
  CHAR* cstring_code = cpc_convert_code_to_cstring( in_code );
  
  if( NULL != cstring_code )
  {
    cpc_log (
             in_log_level,
             in_file,
             in_line_number,
             "Code: %s",
             cstring_code
             );
    
    free( cstring_code );
  }
}
