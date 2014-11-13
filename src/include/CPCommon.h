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
#include "log_definitions.h"
#include "log_functions.h"
#include "error_codes.h"

/*! \def    CPC_CODE_STRING_LENGTH
    \brief  The length of the string representation of a cpc code.
 */
#define CPC_CODE_STRING_LENGTH 7

/*! \def    CPC_PRINT_CODE
    \brief  Wrapper for cpc_print_code to ensure the correct file and line are
            printed in the log message when displaying the string for the error
            code.
 */
#define CPC_PRINT_CODE( in_log_level, in_code ) \
          cpc_print_code( in_log_level, __FILE__, __LINE__, in_code )

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

/*! \fn     void cpc_print_code (
              CPC_LOG_LEVEL  in_log_level,
              CHAR*          in_file,
              INT32          in_line_number,
              OSStatus       in_code
            )
    \brief  Converts in_code to its string representation if possible and
            outputs it using the logger. This function tries to convert return
            codes (UINT32) that have four character representations, i.e. each
            byte is printable.

    \param  in_log_level  The log level to log the converted string
    \param  in_file       The file name to display in the log
    \param  in_line_number  The line number to be displayed in the log
    \param  in_code       The code to convert to its four character string
                          representation.
 */
void
cpc_print_code (
                cpc_log_level  in_log_level,
                CHAR*          in_file,
                INT32          in_line_number,
                UINT32         in_code
                );

/*! \fn     CHAR* cpc_convert_code_to_cstring  (
              UINT32 in_code
            )
    \brief  Converts in_code to its string representation if possible and
            returns the newly created string. This function tries to convert
            UINT32 codes that have four character representations. This function
            will create a new CHAR*, populate it with the string representation
            of the code and return the string. It is up to the caller to free
            the string. A string representation is only generated when possible,
            i.e. when each character is printable.
 
    \param  in_code The code to convert to a c-style string, iff all bytes of
                    in_code are printable ASCII characters.
    \return A newly created string representation of in_code if possible. The
            caller must free the returned string. A NULL string is returned if
            all the bytes of in_code are not printable ASCII.
 */
CHAR*
cpc_convert_code_to_cstring  (
                              UINT32 in_code
                              );

/*! \fn     UINT32 cpc_errno( void )
    \brief  Simply returns the system specific error number field.
 
    \return The platform specific errno.
 */
UINT32
cpc_errno( void );

/*! \fn     CHAR* cpc_strerror  (
              UINT32 in_error
            )
    \brief  Wraps the platform-specific strerror function. Used to translate
            errors in system calls to a string.
 
    \param  in_error  The error to stringify.
    \return The string representation of in_error.
 */
CHAR*
cpc_strerror  (
               UINT32 in_error
               );

/*! \fn     cpc_error_code cpc_safe_malloc (
              void** out_pointer,
              SSIZE  in_pointer_size
            )
    \brief  Creates a safe implementation of malloc. This function will safely
            allocate a new memory buffer, zero it out and return it. If either
            the malloc or memset fail this function will return an error.
            CPC_ERROR_CODE_NO_ERROR is returned otherwise.
    
    \param  out_pointer Upon return out_pointer will point to a newly
                        allocated buffer or NULL if an error occurred.
    \param  in_buffer_size  The size of the buffer to create.
    \return CPC_ERROR_CODE_NO_ERROR(0) if no error has occurred, an error code
            otherwise.
 */
cpc_error_code
cpc_safe_malloc (
                 void** out_pointer,
                 SSIZE  in_buffer_size
                 );

/*! \fn     cpc_error_code cpc_safe_free (
              void** io_pointer
            )
    \brief  This function is a safe impelementation of free. This function
            will free io_pointer if it is a valid pointer and set it to NULL.
            If an error occurs the appropriate error code will be returned.
    
    \param  io_pointer  A pointer to the buffer to be freed.
    \return CPC_ERROR_CODE_NO_ERROR(0) if no error has occurred, an error code
            otherwise.
 */
cpc_error_code
cpc_safe_free (
               void** io_pointer
               );

#endif /* __CPCOMMON_H_ */

