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


