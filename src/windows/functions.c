#include "windows/function_map.h"

#include <string.h>

#define ERROR_STRING_LENGTH   0x100

char error_string[ERROR_STRING_LENGTH] = { '\0' };

void
platform_initialize( void )
{
#ifdef _DEBUG
  // Send all reports to STDOUT
  _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
  _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
  _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
  _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
  _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
  _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );
#endif _DEBUG
}

void
platform_terminate( void )
{
#ifdef _DEBUG
  _CrtDumpMemoryLeaks( );
#endif _DEBUG
}

char*
win_strerror  (
                int in_error
              )
{
  errno_t return_value = strerror_s( error_string, ERROR_STRING_LENGTH, in_error );

  if( 0 == return_value )
  {
    return( error_string );
  }
  else
  {
    return( NULL );
  }
}