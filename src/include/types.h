// This is the cross-platform and cross-architecture standard types file. This
// header is automatically included by CPCommon.h.

#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "target.h"

#if defined( __OSX__ ) || defined( __IOS__ )
  #include <CoreFoundation/CoreFoundation.h>

  #include "darwin/function_map.h"

  typedef int8_t    INT8;
  typedef int16_t   INT16;
  typedef int32_t   INT32;
  typedef int64_t   INT64;
  typedef uint8_t   UINT8;
  typedef uint16_t  UINT16;
  typedef uint32_t  UINT32;
  typedef uint64_t  UINT64;

  typedef Float32   FLOAT32;
  typedef Float64   FLOAT64;

  typedef char          CHAR;
  typedef unsigned char UCHAR;

  typedef ssize_t       SSIZE;
  typedef size_t        USIZE;
#endif

#define TRUE  1
#define FALSE 0

typedef UINT8 BOOL;

#endif /* _TYPES_H_ */

