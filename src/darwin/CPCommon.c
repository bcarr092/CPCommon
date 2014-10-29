#include "CPCommon.h"

INT32
  cpcSprintf  (
               CHAR* restrict outString,
               SIZE inStringLength,
               const CHAR* restrict inStringFormat,
               ...
               )
{
  va_list list;
  
  va_start( list, inStringFormat );
  
  INT32 returnValue =
    snprintf( outString, inStringLength, inStringFormat, list );
  
  va_end( list );
  
  return( returnValue );
}