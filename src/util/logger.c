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

#ifndef NATIVE_BUILD
#define LOGGER_IMPLEMENTATION
#include "EUL/util/logger.h"

#include <string.h>

static void log(const char *levelText, const char *msg);

static Logger_t *loggers[LOGGABLE_COUNT] = {0x00, 0x00};

void logger_addLogger(Logger_t *logger)
{
    for(uint8_t i = 0; i < LOGGABLE_COUNT; i++)
    {
        if(loggers[i] == 0x00)
        {
            loggers[i] = logger;
            break;
        }
    }
}

void logger_init()
{
    for(uint8_t i = 0; i < LOGGABLE_COUNT; i++)
    {
        if(loggers[i] != 0x00)
            loggers[i]->init();
    }
}

#if LOG_LEVEL >= LOG_LEVEL_TRACE
void logger_trace(const char *msg)
{
   log(LOG_LEVEL_TEXT_TRACE, msg);
}
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
void logger_debug(const char *msg) {
    log(LOG_LEVEL_TEXT_DEBUG, msg);
}
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
void logger_info(const char *msg)
{
    log(LOG_LEVEL_TEXT_INFO, msg);
}
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARN
void logger_warn(const char *msg)
{
    log(LOG_LEVEL_TEXT_WARN, msg);
}
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
void logger_error(const char *msg)
{
    log(LOG_LEVEL_TEXT_ERROR, msg);
}
#endif

static void log(const char *levelText, const char *msg)
{
    size_t sizeLevelText = strlen(levelText);
    size_t sizeMessage = strlen(msg);
    //No idea where this -5 comes from but it works xD
    size_t size = sizeLevelText + sizeMessage - 5;
    char totalMsg[size];

    for(size_t i = 0; i < sizeLevelText; i++)
    {
        totalMsg[i] = levelText[i];
    }

    for(size_t i = 0; i < sizeMessage; i++)
    {
        totalMsg[sizeLevelText + i] = msg[i];
    }

    for(size_t i = 0; i < LOGGABLE_COUNT; i++)
    {
        if(loggers[i] != 0x00)
            loggers[i]->log(totalMsg);
    }
}
#endif
