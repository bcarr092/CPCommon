/*! \file   cpcommon.h
    \brief  This is the cross-platform entry point to the cpcommon lib. This is
            the only file that external libraries/binaries should include. All
            platform specfic functionality should be defined in this library
            and implemented in a platform-specific way while presenting a
            common external interface.
 */
#ifndef __CPCOMMON_H_
#define __CPCOMMON_H_

#include <stdio.h>
#include <stdarg.h>

#include "types.h"
#include "log.h"
#include "error_codes.h"

/*! \fn     INT32 cpc_snprintf  (
              CHAR**        io_string,
              USIZE         in_string_length,
              const CHAR*   in_string_format,
              ...
            )
    \brief  Cross-platform wrapper for vsnprintf
 
    \param  io_string Pointer to a buffer that will be created, populated, and
                      returned.
    \param  in_string_length  The length of the buffer, io_string
    \param  in_string_format  The printf formatted format string
    \param  ...       The variable length argument list to use in formatting
                      the string.
    \return Returns either a positive number indicating the number of characters
            that would have been written to io_string if io_string were of
            unlimited length. An error is returned otherwise. See the platform
            specific description for vsnprintf (or equivalent).m
 */
INT32
cpc_snprintf  (
               CHAR**        io_string,
               USIZE         in_string_length,
               const CHAR*   in_string_format,
               ...
               );

/*! \fn     INT32 cpc_printf  (
              const CHAR* in_string_format,
              ...
            )
    \brief  Cross-platform wrapper for vprintf
 
    \param  in_string_format  The printf formatted format string
    \param  ... The variable length argument list to use in formatting the
                output print string.
    \return Returns either the number of characters output, or a negative
            number indicating an error. See the platform specific descrtiption
            of errors for vprintf (or equivalent).
 */
INT32
cpc_printf  (
             const CHAR* in_string_format,
             ...
);

/*! \fn     INT32 cpc_vprintf  (
            const CHAR* in_string_foramt,
            va_list     in_parameters
            )
    \brief  Cross-platform wrapper for vprintf
 
    \param  in_string_format  The printf formatted format string.
    \param  in_list The variable length argument list to use in formatting the
                    output string.
    \return Returns either the number of characters output, or a negative
            number indicating an error. See the platform specific descrtiption
            of errors for vprintf (or equivalent).
 */
INT32
cpc_vprintf  (
              const CHAR* in_string_format,
              va_list     in_list
              );

/*! \fn     INT32 cpc_fprintf (
              FILE* in_handle,
              const CHAR* in_string_format,
              ...
            )
    \brief  Cross-platform wrapper for vfprintf
 
    \param  in_handle The file handle to write the log to.
    \param  in_string_format  The printf formatted format string.
    \param  ... The variable length argument list to use in formatting the
                output print string.
    \return Returns either the number of characters output, or a negative
            number indicating an error. See the platform specific descrtiption
            of errors for vfprintf (or equivalent).
 */
INT32
cpc_fprintf (
             FILE* in_handle,
             const CHAR* in_string_format,
             ...
             );

/*! \fn     INT32 cpc_vfprintf (
            FILE*       in_handle,
            const CHAR* in_string_format,
            va_list     in_parameters
            )
    \brief  Cross-platform wrapper for vfprintf
 
    \param  in_handle The file handle to write the log to.
    \param  in_string_format  The printf formatted format string.
    \param  in_list   The variable length argument list to use in formatting
                      the output print string.
    \return Returns either the number of characters output, or a negative
            number indicating an error. See the platform specific descrtiption
            of errors for vfprintf (or equivalent).
 */
INT32
cpc_vfprintf (
              FILE*       in_handle,
              const CHAR* in_string_format,
              va_list     in_list
              );

#endif /* __CPCOMMON_H_ */

