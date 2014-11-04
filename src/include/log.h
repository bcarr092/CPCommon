#ifndef __LOG_H__
#define __LOG_H__

#include "cpcommon.h"

enum cpc_log_levels
{
  CPC_LOG_LEVEL_TRACE = 0,
  CPC_LOG_LEVEL_DEBUG,
  CPC_LOG_LEVEL_INFO,
  CPC_LOG_LEVEL_WARN,
  CPC_LOG_LEVEL_ERROR
};

typedef INT32 CPC_LOG_LEVEL;

CPC_LOG_LEVEL
  cpc_log  (
              CPC_LOG_LEVEL in_log_level,
              CHAR*         in_log_format,
              ...
           );

void
  cpc_log_set_log_level (
                          CPC_LOG_LEVEL in_new_log_level
                        );

#endif /* __LOG_H__ */
