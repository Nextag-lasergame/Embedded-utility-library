/*
 * Copyright (c) 2020-2021 Tim Herreijgers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef EMBEDDED_UTILITY_LIBRARY_LOGGER_H
#define EMBEDDED_UTILITY_LIBRARY_LOGGER_H

/*
 * TODO:
 *  - Add possibility for configuring your message format
 */

#include <inttypes.h>
#include "loglevels.h"

#define LOG_LEVEL_TEXT_TRACE "[TRACE] "
#define LOG_LEVEL_TEXT_DEBUG "[DEBUG] "
#define LOG_LEVEL_TEXT_INFO  "[INFO]  "
#define LOG_LEVEL_TEXT_WARN  "[WARN]  "
#define LOG_LEVEL_TEXT_ERROR "[ERROR] "

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LOG_LEVEL
#warning LOG_LEVEL not defined, defaulting it to LOG_LEVEL_DEBUG. Please define the LOG_LEVEL as an global define using -DLOG_LEVEL={level here}. Possible log levels: LOG_LEVEL_TRACE, LOG_LEVEL_DEBUG, LOG_LEVEL_INFO, LOG_LEVEL_WARN, LOG_LEVEL_ERROR and LOG_LEVEL_DISABLED
#define LOG_LEVEL LOG_LEVEL_DEBUG
#endif

#ifndef LOGGABLE_COUNT
#define LOGGABLE_COUNT 2
#endif

typedef struct
{
    void (*init)(void);
    void (*log)(const char *);
} Logger_t;

void logger_addLogger(Logger_t *loggable);
void logger_init();
void logger_trace(const char *msg);
void logger_debug(const char *msg);
void logger_info(const char *msg);
void logger_warn(const char *msg);
void logger_error(const char *msg);

#ifndef LOGGER_IMPLEMENTATION

#if LOG_LEVEL >= LOG_LEVEL_TRACE
#define logger_trace(message) logger_trace(message)
#else
#define logger_trace(message)
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define logger_debug(message) logger_debug(message)
#else
#define logger_debug(message)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define logger_info(message) logger_info(message)
#else
#define logger_info(message)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARN
#define logger_warn(message) logger_warn(message)
#else
#define logger_warn(message)
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define logger_error(message) logger_error(message)
#else
#define logger_error(message)
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif //EMBEDDED_UTILITY_LIBRARY_LOGGER_H
