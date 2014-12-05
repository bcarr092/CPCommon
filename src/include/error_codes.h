/*! \file   error_codes.h
    \brief  File containing the enum of errors used by the logger.
 */
#ifndef __ERROR_CODES_H__
#define __ERROR_CODES_H__

#include "types.h"

/*! \enum   cpc_error_codes
    \brief  The error codes used by the logger
 
    \constant CPC_ERROR_CODE_NO_ERROR
                Used to indicate no error.
    \constant CPC_ERROR_CODE_NULL_POINTER
                Code used when an operation is beign attempted on a null pointer
    \constant CPC_ERROR_CODE_INVALID_LOG_LEVEL
                Used by the logger to indicate an unsupported log level has been
                used in a log function.
    \constant CPC_ERROR_CODE_MALLOC
                Used by cpc_safe_malloc to indicate that the system call to
                malloc has failed.
    \constant CPC_ERROR_CODE_MEMSET
                Used by cpc_safe_malloc to indidate that the system call to
                memset has failed.
    \constant CPC_ERROR_CODE_INVALID_PERMISSIONS
                Used when an operation cannot be performed because the correct
                permissions have not been obtained.
 */
enum cpc_error_codes
{
  CPC_ERROR_CODE_NO_ERROR                       = 0,
  CPC_ERROR_CODE_NULL_POINTER                   = -1,
  CPC_ERROR_CODE_INVALID_LOG_LEVEL              = -2,
  CPC_ERROR_CODE_MALLOC                         = -3,
  CPC_ERROR_CODE_MEMSET                         = -4,
  CPC_ERROR_CODE_APPLICATION_INTERRUPTED_IOS    = -5,
  CPC_ERROR_CODE_INVALID_PERMISSIONS            = -6,
  CPC_ERROR_CODE_INVALID_PARAMETER              = -7,
  CPC_ERROR_CODE_API_ERROR                      = -8
};

/*! \var    CPC_ERROR_CODE
    \brief  Type definition for the loggers errors
 */
typedef INT32 cpc_error_code;

#endif /* __ERROR_CODES_H__ */
