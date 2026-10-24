#pragma once

#define ANSI_RED    "\x1b[31m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_CYAN   "\x1b[36m"
#define ANSI_RESET  "\x1b[0m"

#ifdef DEBUG
#include <stdio.h>
#define LOG_ERROR(fmt, ...) LOG(fmt, ANSI_RED "ERROR" ANSI_RESET, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  LOG(fmt, ANSI_YELLOW "WARN" ANSI_RESET, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  LOG(fmt, ANSI_CYAN "INFO" ANSI_RESET, ##__VA_ARGS__)
#define LOG(fmt, level, ...)                                                                       \
    do {                                                                                           \
        (void)fprintf_s(stderr, "[" level "] %s %s (%s:%d)  %s-> " fmt "\n", __DATE__, __TIME__,     \
                      __FILE__, __LINE__, __func__, ##__VA_ARGS__);                                \
    } while (0)
#else
#define LOG_ERROR(fmt, ...) ((void)0)
#define LOG_WARN(fmt, ...)  ((void)0)
#define LOG_INFO(fmt, ...)  ((void)0)
#endif