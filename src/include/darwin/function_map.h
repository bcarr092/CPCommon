#ifndef __FUNCTION_MAP_H__
#define __FUNCTION_MAP_H__

#define \
  CPC_VSNPRINTF( io_string, in_string_length, in_string_format, in_list ) \
    vsnprintf( io_string, in_string_length, in_string_format, in_list )

#define CPC_VPRINTF( in_string_format, inVarArgs ) \
          vprintf( in_string_format, inVarArgs )

#define CPC_VFPRINTF( in_handle, in_string_format, inVarArgs ) \
          vfprintf( in_handle, in_string_format, inVarArgs )

#endif /* __FUNCTION_MAP_H__ */
