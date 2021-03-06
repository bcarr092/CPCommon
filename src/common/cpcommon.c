/*! \file   cpcommon.c
 
    \author Brent Carrara
 */
#include "cpcommon.h"

cpcommon_state g_cpcommon_state = CPCOMMON_STATE_NOT_INITIALIZED;

void
cpc_initialize( void )
{
  switch( g_cpcommon_state )
  {
  case CPCOMMON_STATE_NOT_INITIALIZED:
    g_cpcommon_state = CPCOMMON_STATE_INITIALIZED;

    platform_initialize();

    break;
  case CPCOMMON_STATE_INITIALIZED:
  case CPCOMMON_STATE_TERMINATED:
    CPC_LOG_STRING(
      CPC_LOG_LEVEL_WARN,
      "CPCommon has already been initialized."
      );
    break;
  }
}

void
cpc_terminate( void )
{
  switch( g_cpcommon_state )
  {
  case CPCOMMON_STATE_NOT_INITIALIZED:
    CPC_LOG_STRING( CPC_LOG_LEVEL_ERROR, "CPCommon has not been initialized" );
    break;
  case CPCOMMON_STATE_TERMINATED:
    CPC_LOG_STRING(
      CPC_LOG_LEVEL_WARN,
      "CAHAL has already been terminated"
      );
    break;
  case CPCOMMON_STATE_INITIALIZED:
    g_cpcommon_state = CPCOMMON_STATE_TERMINATED;

    platform_terminate();

    break;
  }
}

CPC_BOOL
cpc_is_initialized( void )
{
  if( CPCOMMON_STATE_INITIALIZED == g_cpcommon_state )
  {
    return( CPC_TRUE );
  }
  else
  {
    return( CPC_FALSE );
  }
}

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
  
  *io_string =
    ( CHAR * ) CPC_MALLOC( sizeof( CHAR ) * ( in_string_length  + 1 ) );
  
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
  
  if( 0 != in_code )
  {
    code = ( CHAR* ) CPC_MALLOC( CPC_CODE_STRING_LENGTH * sizeof( CHAR ) );
    
    if( NULL != code )
    {
      if( code ==
          CPC_MEMSET( code, 0, CPC_CODE_STRING_LENGTH * sizeof( CHAR ) )
         )
      {
        * ( UINT32 * ) ( code + 1 ) = CPC_HTONL( in_code );
        
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
  CHAR* error = CPC_STRERROR( in_error );

  return( error );
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

void
cpc_exit  (
           UINT32 in_exit_code
           )
{
  CPC_LOG (
           CPC_LOG_LEVEL_INFO,
           "Exiting application with code 0x%x.",
           in_exit_code
           );
  
  CPC_EXIT( in_exit_code );
}

cpc_error_code
cpc_strnlen (
    CHAR*   in_string,
    SSIZE*  io_length
            )
{
  cpc_error_code result = CPC_ERROR_CODE_NO_ERROR;

  if( NULL != in_string && NULL != io_length )
  {
    if( 0 < *io_length )
    {
      *io_length = CPC_STRNLEN( in_string, *io_length );
    }
    else
    {
      result = CPC_ERROR_CODE_INVALID_PARAMETER;
    }
  }
  else
  {
    result = CPC_ERROR_CODE_NULL_POINTER;
  }

  return( result );
}

cpc_error_code
cpc_memcpy  (
    void* out_destination,
    void* in_source,
    SSIZE in_num_bytes
            )
{
  cpc_error_code result = CPC_ERROR_CODE_NO_ERROR;

  if( NULL != out_destination && NULL != in_source )
  {
    if( 0 < in_num_bytes )
    {
      CPC_MEMCPY( out_destination, in_source, in_num_bytes );
    }
    else
    {
      result = CPC_ERROR_CODE_INVALID_PARAMETER;
    }
  }
  else
  {
    result = CPC_ERROR_CODE_NULL_POINTER;
  }

  return( result );
}

cpc_error_code
cpc_safe_realloc  (
    void**  io_pointer,
    SSIZE   in_original_size,
    SSIZE   in_new_size
                  )
{
  cpc_error_code result = CPC_ERROR_CODE_NO_ERROR;

  if( NULL != io_pointer )
  {
    void* destination = NULL;

    result = cpc_safe_malloc( &destination, in_new_size );

    if( CPC_ERROR_CODE_NO_ERROR == result )
    {
      if( NULL != *io_pointer && 0 < in_original_size )
      {
        result = cpc_memcpy( destination, *io_pointer, in_original_size );

        if( CPC_ERROR_CODE_NO_ERROR == result )
        {
          cpc_safe_free( io_pointer );
        }
      }

      *io_pointer = destination;
    }
  }
  else
  {
    result = CPC_ERROR_CODE_NULL_POINTER;
  }

  return( result );
}

UINT32
cpc_min_UINT32  (
                 UINT32 in_a,
                 UINT32 in_b
                 )
{
  if( in_a < in_b )
  {
    return( in_a );
  }
  else
  {
    return( in_b );
  }
}

USIZE
cpc_min_USIZE  (
                 USIZE in_a,
                 USIZE in_b
                 )
{
  if( in_a < in_b )
  {
    return( in_a );
  }
  else
  {
    return( in_b );
  }
}

FLOAT32
cpc_min_FLOAT32 (
                 FLOAT32 in_a,
                 FLOAT32 in_b
                 )
{
  if( in_a < in_b )
  {
    return( in_a );
  }
  else
  {
    return( in_b );
  }
}

FLOAT64
cpc_min_FLOAT64 (
                 FLOAT64 in_a,
                 FLOAT64 in_b
                 )
{
  if( in_a < in_b )
  {
    return( in_a );
  }
  else
  {
    return( in_b );
  }
}

CPC_BOOL
cpc_check_if_file_exists  (
                           CHAR* in_file_name
                           )
{
  CPC_BOOL return_value = CPC_FALSE;
  FILE *file            = NULL;

  CPC_FOPEN( file, in_file_name, "r" );
  
  if( file )
  {
    CPC_LOG( CPC_LOG_LEVEL_TRACE, "File %s exists.", in_file_name );
    
    return_value = CPC_TRUE;
    
    fclose( file );
  }
  else
  {
    CPC_LOG( CPC_LOG_LEVEL_TRACE, "File %s does not exist.", in_file_name );
  }
  
  return( return_value );
}

FLOAT64
cpc_bessel_i0 (
               FLOAT64 in_number
               )
{
  FLOAT64 ax  = 0;
  FLOAT64 ans = 0;
  FLOAT64 y   = 0;
  
  if( ( ax = fabs( in_number ) ) < 3.75 )
  {
    y =   in_number / 3.75;
    y *=  y;
    
    ans =
      1.0 + y * ( 3.5156229 + y * ( 3.0899424 + y * ( 1.2067492
      + y * ( 0.2659732 + y * ( 0.360768e-1 + y * 0.45813e-2 ) ) ) ) );
  }
  else
  {
    y = 3.75 / ax;
    
    ans =
      ( CPC_EXP( FLOAT64, ax ) / CPC_SQRT( FLOAT64, ax ) ) * ( 0.39894228
      + y * ( 0.1328592e-1 + y * ( 0.225319e-2 + y * ( -0.157565e-2
      + y * ( 0.916281e-2 + y * ( -0.2057706e-1 + y * ( 0.2635537e-1
      + y * ( -0.1647633e-1 + y * 0.392377e-2 ) ) ) ) ) ) ) );
  }
  return ans;
}
