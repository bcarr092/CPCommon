/*! \file   types.h
    \brief  This is the cross-platform and cross-architecture standard types
            file. This header is automatically included by cpcommon.h.
 
    \author Brent Carrara
*/

#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "target.h"

#if defined( __OSX__ ) || defined( __IOS__ )
  #include <CoreFoundation/CoreFoundation.h>

  #include "darwin/function_map.h"

  #ifdef __OSX__
    typedef int8_t    INT8;
    typedef int16_t   INT16;
    typedef int32_t   INT32;
    typedef int64_t   INT64;
    typedef uint8_t   UINT8;
    typedef uint16_t  UINT16;
    typedef uint32_t  UINT32;
    typedef uint64_t  UINT64;
  #else
    typedef SInt8    INT8;
    typedef SInt16   INT16;
    typedef SInt32   INT32;
    typedef SInt64   INT64;
    typedef UInt8   UINT8;
    typedef UInt16  UINT16;
    typedef UInt32  UINT32;
    typedef UInt64  UINT64;
  #endif

  typedef Float32   FLOAT32;
  typedef Float64   FLOAT64;

  typedef char          CHAR;
  typedef unsigned char UCHAR;

  typedef ssize_t       SSIZE;
  typedef size_t        USIZE;
#elif defined( __ANDROID__ )
  #include <errno.h>
  #include <ctype.h>

  #include <arpa/inet.h>

  #include "android/function_map.h"

  typedef int8_t    INT8;
  typedef int16_t   INT16;
  typedef int32_t   INT32;
  typedef int64_t   INT64;
  typedef uint8_t   UINT8;
  typedef uint16_t  UINT16;
  typedef uint32_t  UINT32;
  typedef uint64_t  UINT64;

  typedef float   FLOAT32;
  typedef double  FLOAT64;

  typedef char          CHAR;
  typedef unsigned char UCHAR;

  typedef ssize_t       SSIZE;
  typedef UINT32        USIZE;
#elif defined( __WIN32__ )
  #include <Windows.h>
  #include <windef.h>
  #include <winnt.h>
  #include <BaseTsd.h>

  #include "windows/function_map.h"

  typedef int8_t    INT8;
  typedef int16_t   INT16;
  typedef int32_t   INT32;
  typedef int64_t   INT64;
  typedef uint8_t   UINT8;
  typedef uint16_t  UINT16;
  typedef uint32_t  UINT32;
  typedef uint64_t  UINT64;

  typedef float   FLOAT32;
  typedef double  FLOAT64;

  typedef char          CHAR;
  typedef unsigned char UCHAR;

  typedef SSIZE_T       SSIZE;
  typedef UINT32        USIZE;
#endif

/*! \def    CPC_TRUE
    \brief  True constant used by the CPCommon library.
 */
#define CPC_TRUE  1

/*! \def    CPC_FALSE
    \brief  False constant used by the CPCommon library.
 */
#define CPC_FALSE 0

/*! \var    CPC_BOOL
    \brief  We use a char to store boolean values.
 */
typedef UINT8 CPC_BOOL;

#define MAX_INT8  SCHAR_MAX
#define MIN_INT8  SCHAR_MIN
#define MAX_INT16 SHRT_MAX
#define MIN_INT16 SHRT_MIN
#define MAX_INT32 INT_MAX
#define MIN_INT32 INT_MIN
#define MAX_INT64 LONG_MAX
#define MIN_INT64 LONG_MIN

#define MAX_UINT8   UCHAR8
#define MIN_UINT8   0
#define MAX_UINT16  USHRT_MAX
#define MIN_UINT16  0
#define MAX_UINT32  UINT_MAX
#define MIN_UINT32  0
#define MAX_UINT64  ULONG_MAX
#define MIN_UINT64  0

#endif /* _TYPES_H_ */

