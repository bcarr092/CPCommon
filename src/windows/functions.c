#include "windows/function_map.h"

#include <string.h>

#define ERROR_STRING_LENGTH   0x100

char error_string[ERROR_STRING_LENGTH] = { '\0' };

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