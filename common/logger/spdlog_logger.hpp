#pragma once

// HACK... somehow doesn't get propagated
#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#endif
#include <spdlog/spdlog.h>

#define TRACE_(...)   spdlog::trace(__VA_ARGS__)
#define DEBUG_(...)   spdlog::debug(__VA_ARGS__)
#define INFO_(...)    spdlog::info(__VA_ARGS__)
#define WARN_(...)    spdlog::warn(__VA_ARGS__)
#define ERROR_(...)   spdlog::error(__VA_ARGS__)
#define FATAL_(...)   spdlog::critical(__VA_ARGS__)
