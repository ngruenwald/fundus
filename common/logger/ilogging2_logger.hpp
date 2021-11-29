#pragma once

#include <ilogging2.h>

#define TRACE_(x)   EF_LOG(TRACE, x)
#define DEBUG_(x)   EF_LOG(DEBUG, x)
#define INFO_(x)    EF_LOG(INFO, x)
#define WARN_(x)    EF_LOG(WARN, x)
#define ERROR_(x)   EF_LOG(ERROR, x)
#define FATAL_(x)   EF_LOG(FATAL, x)
#define NOTIFY_(x)  EF_LOG(INFO, x)
