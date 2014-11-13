#include "cpcommon.h"

INT32
cpc_snprintf  (
               CHAR**        io_string,
               USIZE         in_string_length,
               const CHAR*   in_string_format,
               ...
               )
{
  INT32 return_value = -1;
  va_list list;
  
  va_start( list, in_string_format );
  
  *io_string = ( CHAR * ) CPC_MALLOC( sizeof( CHAR ) * in_string_length );
  
  if( NULL != *io_string )
  {
    if( *io_string ==
       CPC_MEMSET( *io_string, 0x0, ( in_string_length + 1 ) )
       )
    {
      return_value =
        CPC_VSNPRINTF( *io_string, in_string_length, in_string_format, list );
    }
    else
    {
      cpc_safe_free( ( void** ) io_string );
    }
  }
  
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
    code = ( CHAR* ) CPC_MALLOC( CPC_CODE_STRING_LENGTH * sizeof( CHAR ) );
    
    if( NULL != code )
    {
      if( code ==
          CPC_MEMSET( code, 0, CPC_CODE_STRING_LENGTH * sizeof( CHAR ) )
         )
      {
        * ( UINT32 * ) ( code + 1 ) = CFSwapInt32HostToBig( in_code );
        
        if( isprint( code[ 1 ] ) && isprint( code[ 2 ] )
           && isprint( code[ 3 ] ) && isprint( code[ 4 ] ) )
        {
          code[ 0 ] = code[ 5 ] = '\'';
          code[ 6 ] = '\0';
        }
      }
      else
      {
        cpc_safe_free( ( void** ) &code );
      }
    }
  }
  
  return( code );
}

void
cpc_print_code (
                cpc_log_level  in_log_level,
                CHAR*          in_file,
                INT32          in_line_number,
                UINT32         in_code
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

UINT32
cpc_errno( void )
{
  return( CPC_ERRNO );
}

CHAR*
cpc_strerror  (
               UINT32 in_error
               )
{
  return( CPC_STRERROR( in_error ) );
}

cpc_error_code
cpc_safe_malloc (
                 void** out_pointer,
                 SSIZE  in_buffer_size
                 )
{
  if( NULL != out_pointer )
  {
    *out_pointer = CPC_MALLOC( in_buffer_size );
    
    if( NULL != *out_pointer )
    {
      if( *out_pointer == CPC_MEMSET( *out_pointer, 0, in_buffer_size ) )
      {
        return( CPC_ERROR_CODE_NO_ERROR );
      }
      else
      {
        CPC_ERROR (
                   "Could not memset (%d): %s.",
                   CPC_ERRNO,
                   CPC_STRERROR( CPC_ERRNO )
                   );
        
        cpc_safe_free( out_pointer );
        
        return( CPC_ERROR_CODE_MEMSET );
      }
    }
    else
    {
      CPC_ERROR (
                 "Could not malloc (%d): %s.",
                 CPC_ERRNO,
                 CPC_STRERROR( CPC_ERRNO )
                 );
      
      return( CPC_ERROR_CODE_MALLOC );
    }
  }
  else
  {
    CPC_LOG_STRING( CPC_LOG_LEVEL_ERROR, "Null pointer." );
    
    return( CPC_ERROR_CODE_NULL_POINTER );
  }
}

cpc_error_code
cpc_safe_free (
               void** io_pointer
               )
{
  if( NULL != io_pointer )
  {
    if( NULL != *io_pointer )
    {
      CPC_FREE( *io_pointer );
      
      *io_pointer = NULL;
    }
    
    return( CPC_ERROR_CODE_NO_ERROR );
  }
  else
  {
    return( CPC_ERROR_CODE_NULL_POINTER );
  }
}
