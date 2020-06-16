#define LOGGER_IMPLEMENTATION
#include "EUL/util/logger.h"

#include <string.h>
#include <avr/io.h>

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
    size_t size = sizeLevelText + sizeMessage - 3;
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
