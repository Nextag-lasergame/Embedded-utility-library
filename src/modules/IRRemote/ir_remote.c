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

#include "EUL/modules/IRRemote/ir_remote.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <EUL/EUL.h>

#include "avr/io.h"

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

#define IR_38KHZ_PERIOD_MS (1.0 / 38.0)
#define IR_50KHZ_PERIOD_MS (1.0 / 25.0)

#define SAMSUNG_START_BIT_UP ((int) (4.5 / IR_38KHZ_PERIOD_MS))
#define SAMSUNG_START_BIT_DOWN SAMSUNG_START_BIT_UP
#define SAMSUNG_BIT_UP_ONE ((int) (0.590 / IR_38KHZ_PERIOD_MS))
#define SAMSUNG_BIT_UP_ZERO SAMSUNG_BIT_UP_ONE
#define SAMSUNG_BIT_DOWN_ONE ((int) (1.690 / IR_38KHZ_PERIOD_MS))
#define SAMSUNG_BIT_DOWN_ZERO SAMSUNG_BIT_UP_ONE
#define SAMSUNG_STOP_BIT_UP SAMSUNG_BIT_UP_ONE
#define SAMSUNG_STOP_BIT_DOWN SAMSUNG_BIT_UP_ONE

#define STATE_RECEIVING 1
#define STATE_TRANSMITTING 2
#define STATE_IDLE 0
static uint8_t sState = STATE_IDLE;

static uint32_t ir_readSamsung();

static void ir_setFreqKHz(enum Frequency freq);
static void ir_switchState(uint8_t state);
static void ir_timerCallbackTransmit();
static void ir_timerCallbackReceive();
static void ir_timerCallback();

static Timer_t sTimer;
static Pin_t sPin;
static uint8_t sIndex = 0;
static uint16_t sCount = 0;
static uint8_t *sSendDataBuffer = 0x00;
static uint8_t sSendDataBufferSize = 0;
static uint16_t sDataBufferArray[70];
static uint8_t sTimerUpDownCounter = 0;
static uint8_t sDataBufferArraySize = 0;
static float sDataReceiveStepIntervalMs = 0;
static bool lastState = true;
static bool sReceiving = false;

void ir_init(Timer_t timer, Pin_t pin)
{
    sTimer = timer;
    sPin = pin;

    dio_setDirection(sPin, true);
    timer_enableInterruptCompA(timer, true);
    timer_setCompAVectCallback(timer, ir_timerCallback);
    timer_setMode(timer, CTC);
    ir_setFreqKHz(FREQ_50_KHZ);

    ir_switchState(STATE_RECEIVING);
}

void ir_stop()
{
    sState = STATE_IDLE;
    ir_setFreqKHz(FREQ_DISABLED);
}

void ir_sendSamsungRaw(uint32_t data)
{
    while (sState == STATE_TRANSMITTING);
    ir_switchState(STATE_TRANSMITTING);
    // 170 cycles on and off for start bit
    // 32 bits
    // on bit 22 cycles on, 64 cycles off
    // off bit 22 cycles on, 22 cycles off
    // stop bit 22 cycles on, 22 cycles off
    // LSB first (inverted)
    sIndex = 0;
    sCount = 0;
    sSendDataBufferSize = 68; // 2 for start, 2 * 32 for data and 2 for stop bytes.
    sSendDataBuffer = malloc(sizeof(uint8_t) * sSendDataBufferSize);
    sSendDataBuffer[0] = SAMSUNG_START_BIT_UP;
    sSendDataBuffer[1] = SAMSUNG_START_BIT_DOWN;

    for(int32_t i = 0; i < 32; i++)
    {
        if(data & (((uint32_t) 1) << i))
        {
            sSendDataBuffer[sSendDataBufferSize - (2 + (i * 2))] = SAMSUNG_BIT_UP_ONE;
            sSendDataBuffer[sSendDataBufferSize - (2 + (i * 2) + 1)] = SAMSUNG_BIT_DOWN_ONE;
        }
        else
        {
            sSendDataBuffer[sSendDataBufferSize - (2 + (i * 2))] = SAMSUNG_BIT_UP_ZERO;
            sSendDataBuffer[sSendDataBufferSize - (2 + (i * 2) + 1)] = SAMSUNG_BIT_DOWN_ZERO;
        }
    }

    sSendDataBuffer[sSendDataBufferSize - 2] = SAMSUNG_STOP_BIT_UP;
    sSendDataBuffer[sSendDataBufferSize - 1] = SAMSUNG_STOP_BIT_DOWN;

    ir_setFreqKHz(FREQ_38_KHZ);
}

bool ir_available()
{
    return !sReceiving && sDataBufferArraySize > 0;
}

uint32_t ir_read()
{
#if 0
    char buffer[10];
    itoa(sDataBufferArraySize, buffer, 10);
    logln(buffer);

    for (int i = 0; i < sDataBufferArraySize; i ++) {
        itoa(sDataBufferArray[i], buffer, 10);
        if(i % 2 == 0)
        {
            log("+");
            log(buffer);
        }
        else
        {
            log(", -");
            logln(buffer);
        }
    }
#endif

    uint32_t data = 0x00000000;

    // Check if start bit is samsung protocol
    if (sDataBufferArraySize >= 67 && sDataBufferArray[0] >= 110 && sDataBufferArray[1] >= 110 &&
        sDataBufferArray[0] <= 114 && sDataBufferArray[1] <= 114)
    {
        data = ir_readSamsung();
    }

    sDataBufferArraySize = 0;
    return data;
}

static uint32_t ir_readSamsung()
{
    uint32_t data = 0x00000000;
    for(int i = 0; i < 32; i++)
    {
        if (sDataBufferArray[(i * 2) + 3] > 30)
            data |= ((uint32_t) 1 << (31 - i));
    }
    return data;
}

static void ir_setFreqKHz(enum Frequency freq)
{
    log("Setting frequency to ");
    switch (freq) {
        case FREQ_38_KHZ:
            logln("38kHz");
            timer_setMaxCompA(sTimer, 210);
            timer_setPrescaler(sTimer, PRESCALER_1);
            sDataReceiveStepIntervalMs = IR_38KHZ_PERIOD_MS;
            break;
        case FREQ_50_KHZ:
            logln("25kHz");
            timer_setMaxCompA(sTimer, 80);
            timer_setPrescaler(sTimer, PRESCALER_8);
            sDataReceiveStepIntervalMs = IR_50KHZ_PERIOD_MS;
            break;
        default:
            logln("0kHz");
            timer_setMaxCompA(sTimer, 0);
            timer_setPrescaler(sTimer, PRESCALER_0);
            sDataReceiveStepIntervalMs = 0;
            break;
    }
}

static void ir_switchState(uint8_t state)
{
    switch (state) {
        case STATE_TRANSMITTING:
            sState = STATE_TRANSMITTING;
            dio_setDirection(sPin, true);
            break;
        case STATE_RECEIVING:
            sState = STATE_RECEIVING;
            sTimerUpDownCounter = 0;
            sDataBufferArraySize = 0;
            sDataReceiveStepIntervalMs = 0;
            lastState = false;
            dio_setDirection(sPin, false);
            lastState = dio_getInput(sPin);
            break;
        default:
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

    if(sCount >= sSendDataBuffer[sIndex] * 2)
    {
        sCount = 0;
        sIndex++;

        if(sIndex >= sSendDataBufferSize)
        {
            ir_switchState(STATE_RECEIVING);
            free(sSendDataBuffer);
            ir_setFreqKHz(FREQ_50_KHZ);
            return;
        }
    }
}

static void ir_timerCallbackReceive()
{
    // sTimerUpDownCounter
    // sDataBufferArraySize
    bool active = dio_getInput(sPin);
    if(active != lastState)
    {
        sReceiving = true;
        if(sTimerUpDownCounter != 0)
        {
            // TODO: This is to prevent a buffer overflow, add overflow option when returning struct instead of only the data
            //  Not needed yet, because we only handle samsung ir protocol. When adding other protocols we should
            //  really return a struct with more data.
            if(sDataBufferArraySize < 70)
                sDataBufferArray[sDataBufferArraySize] = sTimerUpDownCounter;
            sTimerUpDownCounter = 0;
            sDataBufferArraySize++;
        }
    }

    if (sReceiving)
    {
        sTimerUpDownCounter++;
        if(sTimerUpDownCounter > 254) {
            sReceiving = false;
            sTimerUpDownCounter = 0;
        }
    }

    lastState = active;
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

#endif