#ifndef __CPCOMMON_H_
#define __CPCOMMON_H_

#include <stdarg.h>

#include "types.h"

/**
 *  Cross-platform wrapper for snprintf
 *
 *  @param  ioString  Pointer to a buffer that will be created, populated, and
                      returned.
 *  @param  inStringLength  The length of the buffer, outString
 *  @param  inStringFormat  The printf formatted format string
 *  @param  ...       The variable length argument list to use in formatting
 *                    the string.
 *  @return Returns either a positive number indicating the number of characters
 *          that would have been written to outString if outString were of
 *          unlimited length. An error is returned otherwise.
 */
INT32
  cpc_snprintf  (
                  CHAR** ioString,
                  SIZE inStringLength,
                  const CHAR* inStringFormat,
                  ...
                 );

#endif /* __CPCOMMON_H_ */

