/*! \file   function_map.h
    \brief  File that maps the platform indepent functions to the platform
            specific functions by using macros.
 */
#ifndef __FUNCTION_MAP_H__
#define __FUNCTION_MAP_H__

#define CPC_ERRNO errno

/*! \def    CPC_VSNPRINTF
    \brief  Macro that maps to the platform specific vsnprintf function.
 */
#define \
  CPC_VSNPRINTF( io_string, in_string_length, in_string_format, in_list ) \
    vsnprintf( io_string, in_string_length, in_string_format, in_list )

/*! \def    CPC_VPRINTF
    \brief  Macro that maps to the platform specific vprintf function.
 */
#define CPC_VPRINTF( in_string_format, inVarArgs ) \
          vprintf( in_string_format, inVarArgs )

/*! \def    CPC_VFPRINTF
    \brief  Macro that maps to the platform spcecific vfprintf function.
 */
#define CPC_VFPRINTF( in_handle, in_string_format, inVarArgs ) \
          vfprintf( in_handle, in_string_format, inVarArgs )

/*! \def    CPC_STRERROR
    \brief  Macro that maps to the platform specific strerror function.
 */
#define CPC_STRERROR( in_error ) strerror( in_error )

/*! \def    CPC_MALLOC
    \brief  Macro that maps to the platform specific malloc function.
 */
#define CPC_MALLOC( in_buffer_size ) malloc( in_buffer_size )

/*! \def    CPC_MEMSET
    \brief  Macro that maps to the platform specific memset function.
 */
#define CPC_MEMSET( io_buffer, in_value, in_buffer_size ) \
          memset( io_buffer, in_value, in_buffer_size )

/*! \def    CPC_FREE
    \brief  Macro that maps to the platfrom specific free function.
 */
#define CPC_FREE( in_buffer ) free( in_buffer )

/*! \def    CPC_EXIT
    \brief  Macro that maps to the platform specific exit function.
 */
#define CPC_EXIT( in_exit_code )  exit( in_exit_code )

/*! \def    CPC_HTONL
    \brief  Macro that maps to the platform specific htonl function.
 */
#define CPC_HTONL( in_to_convert )  CFSwapInt32HostToBig( in_to_convert )

#define CPC_STRNLEN( in_string, in_max_length ) \
  strnlen( in_string, in_max_length )

#define CPC_MEMCPY( out_destination, in_source, in_num_bytes )  \
  memcpy( out_destination, in_source, in_num_bytes )

#endif /* __FUNCTION_MAP_H__ */
