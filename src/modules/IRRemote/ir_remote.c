//
// Created by timti on 18/01/2021.
//

#include "EUL/modules/IRRemote/ir_remote.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <EUL/EUL.h>

#ifdef EUL_TEST_BUILD
#define log(x) while(!usart_print(x))
#define logln(x) while(!usart_println(x))
#else
#define log(x)
#define logln(x)
#endif

enum Frequency {
    FREQ_DISABLED,
    FREQ_38_KHZ,
    FREQ_50_KHZ
};

#define STATE_RECEIVING 1
#define STATE_TRANSMITTING 2
#define STATE_IDLE 0
static uint8_t sState = STATE_IDLE;

static void ir_setFreqKHz(enum Frequency freq);
static void ir_timerCallbackTransmit();
static void ir_timerCallbackReceive();
static void ir_timerCallback();

static Timer_t sTimer;
static uint32_t sPin;
static uint8_t sIndex = 0;
static uint16_t sCount = 0;
static uint8_t *sSendDataBuffer = 0x00;
static uint8_t sSendDataBufferSize = 0;

void ir_init(Timer_t timer, uint32_t pin)
{
    sTimer = timer;
    sPin = pin;

    dio_setDirection(sPin, true);
    timer_enableInterruptCompA(timer, true);
    timer_setCompAVectCallback(timer, ir_timerCallback);
    timer_setMode(timer, CTC);
    ir_setFreqKHz(FREQ_50_KHZ);

    sState = STATE_RECEIVING;
}

void ir_sendSamsungRaw(uint32_t data)
{
    while (sState == STATE_TRANSMITTING);
    sState = STATE_TRANSMITTING;
    // 170 cycles on and off for start bit
    // 32 bits
    // on bit 22 cycles on, 64 cycles off
    // off bit 22 cycles on, 22 cylces off
    // stop bit 22 cycles on, 22 cycles off
    // LSB first (inverted)
    sIndex = 0;
    sCount = 0;
    sSendDataBufferSize = 68; // 2 for start, 2 * 32 for data and 2 for stop bytes.
    sSendDataBuffer = malloc(sizeof(uint8_t) * sSendDataBufferSize);
    sSendDataBuffer[0] = 170;
    sSendDataBuffer[1] = 170;

    for(int32_t i = 0; i < 32; i++)
    {
        if(data & (((uint32_t) 1) << i))
        {
            sSendDataBuffer[sSendDataBufferSize - (2 + (i * 2))] = 22;
            sSendDataBuffer[sSendDataBufferSize - (2 + (i * 2) + 1)] = 64;
        }
        else
        {
            sSendDataBuffer[sSendDataBufferSize - (2 + (i * 2))] = 22;
            sSendDataBuffer[sSendDataBufferSize - (2 + (i * 2) + 1)] = 22;
        }
    }

    sSendDataBuffer[sSendDataBufferSize - 2] = 22;
    sSendDataBuffer[sSendDataBufferSize - 1] = 22;

    ir_setFreqKHz(FREQ_38_KHZ);
}

static void ir_setFreqKHz(enum Frequency freq)
{
    log("Setting frequency to ");
    switch (freq) {
        case FREQ_38_KHZ:
            logln("38kHz");
            timer_setMaxCompA(sTimer, 212);
            timer_setPrescaler(sTimer, PRESCALER_1);
            break;
        case FREQ_50_KHZ:
            logln("50kHz");
            timer_setMaxCompA(sTimer, 40);
            timer_setPrescaler(sTimer, PRESCALER_8);
            break;
        default:
            logln("0kHz");
            timer_setMaxCompA(sTimer, 0);
            timer_setPrescaler(sTimer, PRESCALER_0);
            break;
    }
}

static void ir_timerCallbackTransmit()
{
    if(sIndex % 2 == 0)
        dio_setOutput(sPin, !dio_getInput(sPin));
    else
        dio_setOutput(sPin, false);

    sCount++;

    if((sCount / 2) >= sSendDataBuffer[sIndex])
    {
        sCount = 0;
        sIndex++;

        if(sIndex >= sSendDataBufferSize)
        {
            free(sSendDataBuffer);
            ir_setFreqKHz(FREQ_50_KHZ);
            sState = STATE_RECEIVING;
            return;
        }
    }
}

static void ir_timerCallbackReceive()
{

}

static void ir_timerCallback()
{
    switch (sState) {
        case STATE_TRANSMITTING:
            ir_timerCallbackTransmit();
            break;
        case STATE_RECEIVING:
            ir_timerCallbackReceive();
            break;
        default:
            break;
    }
}