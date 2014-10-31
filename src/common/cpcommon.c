#include "../include/cpcommon.h"

INT32
  cpc_snprintf  (
            CHAR** ioString,
               SIZE inStringLength,
               const CHAR* inStringFormat,
               ...
               )
{
  va_list list;
  
  va_start( list, inStringFormat );
  
  *ioString = ( CHAR * ) malloc( sizeof( CHAR ) * ( inStringLength + 1 ));
    
  memset( *ioString, 0x0, ( inStringLength + 1 ) );
  
  INT32 returnValue =
    CPC_VSNPRINTF( *ioString, inStringLength, inStringFormat, list );
  
  va_end( list );
  
  return( returnValue );
}

