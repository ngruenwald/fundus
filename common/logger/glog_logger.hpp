#pragma once

#undef ERROR
#include <glog/logging.h>

#define TRACE_(x)   LOG(DEBUG) << x
#define DEBUG_(x)   LOG(DEBUG) << x
#define INFO_(x)    LOG(INFO) << x
#define WARN_(x)    LOG(WARNING) << x
#define ERROR_(x)   LOG(ERROR) << x
#define FATAL_(x)   LOG(FATAL) << x
