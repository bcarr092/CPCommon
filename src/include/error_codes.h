/*! \file   error_codes.h
    \brief  File containing the enum of errors used by the logger.
 */
#ifndef __ERROR_CODES_H__
#define __ERROR_CODES_H__

#include "types.h"

/*! \enum   cpc_error_codes
    \brief  The error codes used by the logger
 */
enum cpc_error_codes
{
  CPC_ERROR_CODE_NO_ERROR           = 0,
  CPC_ERROR_CODE_INVALID_LOG_LEVEL
};

/*! \var    CPC_ERROR_CODE
    \brief  Type definition for the loggers errors
 */
typedef INT32 CPC_ERROR_CODE;

#endif /* __ERROR_CODES_H__ */
