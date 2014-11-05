/*! \file   function_map.h
    \brief  File that maps the platform indepent functions to the platform
            specific functions by using macros.
 */
#ifndef __FUNCTION_MAP_H__
#define __FUNCTION_MAP_H__

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

#endif /* __FUNCTION_MAP_H__ */
