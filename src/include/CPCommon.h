  #ifndef __CPCOMMON_H_
#define __CPCOMMON_H_

#include <stdio.h>
#include <stdarg.h>

#include "types.h"
#include "log.h"
#include "error_codes.h"

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
 *          unlimited length. An error is returned otherwise. See the platform
 *          specific description for vsnprintf (or equivalent)
 */
INT32
  cpc_snprintf  (
                  CHAR**        io_string,
                  USIZE         in_string_length,
                  const CHAR*   in_string_format,
                  ...
                 );

INT32
  cpc_vprintf  (
                const CHAR* in_string_foramt,
                va_list     in_parameters
              );

INT32
  cpc_vfprintf (
                FILE*       in_handle,
                const CHAR* in_string_format,
                va_list     in_parameters
              );

#endif /* __CPCOMMON_H_ */

