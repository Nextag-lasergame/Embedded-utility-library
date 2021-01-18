#ifdef EUL_TEST_BUILD

#define F_CPU 16000000L

#define assert_true(statement, message) if(!statement) logger_debug(message)

#include <EUL/EUL.h>

void compACallback();
bool enabled = true;
uint32_t led = DIO_PB0;

int main()
{
    logger_addLogger(&usartLogger115200);
    logger_init();

    dio_setDirection(led, true);

    logger_debug("Starting boot procedure\n");

    Timer_t timer = 0;
    timer_setMode(timer, CTC);
    assert_true(timer_enableInterruptCompA(timer, true), "Enabling interrupt failed\n");
    assert_true(timer_setMaxCompA(timer, 210), "Setting max compa a failed\n");
    assert_true(timer_setCompAVectCallback(timer, compACallback), "Setting callback failed\n");
    if (!timer_setPrescaler(timer, PRESCALER_1))
        logger_debug("Timer1 failed\n");

    for(;;)
    {
    }
}

void compACallback()
{
    dio_setOutput(led, enabled);
    enabled = !enabled;
}

#endif