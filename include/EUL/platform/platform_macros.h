#ifndef EMBEDDED_UTILITY_LIBRARY_PLATFORM_MACROS_H
#define EMBEDDED_UTILITY_LIBRARY_PLATFORM_MACROS_H

#define PIN_SHIFT(x) ((uint64_t) x << (uint64_t) 48)
#define DDR_SHIFT(x) ((uint64_t) x << (uint64_t) 32)
#define PORT_SHIFT(x) ((uint64_t) x << (uint64_t) 16)
#define BIT_SHIFT(x) ((uint64_t) x)

#define TIMER_CONTROLA_SHIFT(x) ((uint64_t) x << 56)
#define TIMER_CONTROLB_SHIFT(x) ((uint64_t) x << 48)
#define TIMER_OUTPUTA_SHIFT(x) ((uint64_t) x << 40)
#define TIMER_INTERRUPT_SHIFT(x) ((uint64_t) x << 32)
#define TIMER_PRESCALERS(x) ((uint64_t) x << 2)
#define TIMER_FLAGS(x) ((uint64_t) x)

#define TIMER_CONTROLA_SHIFT(x) ((uint64_t) x << 56)
#define TIMER_OUTPUTA_SHIFT(x) ((uint64_t) x << 48)
#define TIMER_INTERRUPT_SHIFT(x) ((uint64_t) x << 32)
#define TIMER_PRESCALERS(x) ((uint64_t) x << 8)
#define TIMER_FLAGS(x) ((uint64_t) x)

#define TIMER_PRESCALER_1_OFFSET (3 * 0)
#define TIMER_PRESCALER_8_OFFSET (3 * 1)
#define TIMER_PRESCALER_32_OFFSET (3 * 2)
#define TIMER_PRESCALER_64_OFFSET (3 * 3)
#define TIMER_PRESCALER_128_OFFSET (3 * 4)
#define TIMER_PRESCALER_256_OFFSET (3 * 5)
#define TIMER_PRESCALER_1024_OFFSET (3 * 6)
#define TIMER_PRESCALER_EXTERNAL_RISING_OFFSET (3 * 7)
#define TIMER_PRESCALER_EXTERNAL_FALLING_OFFSET (3 * 8)

#define TIMER_PRESCALER_1(x) ((uint64_t) x << TIMER_PRESCALER_1_OFFSET)
#define TIMER_PRESCALER_8(x) ((uint64_t) x << TIMER_PRESCALER_8_OFFSET)
#define TIMER_PRESCALER_32(x) ((uint64_t) x << TIMER_PRESCALER_32_OFFSET)
#define TIMER_PRESCALER_64(x) ((uint64_t) x << TIMER_PRESCALER_64_OFFSET)
#define TIMER_PRESCALER_128(x) ((uint64_t) x << TIMER_PRESCALER_128_OFFSET)
#define TIMER_PRESCALER_256(x) ((uint64_t) x << TIMER_PRESCALER_256_OFFSET)
#define TIMER_PRESCALER_1024(x) ((uint64_t) x << TIMER_PRESCALER_1024_OFFSET)
#define TIMER_PRESCALER_EXTERNAL_RISING(x) ((uint64_t) x << TIMER_PRESCALER_EXTERNAL_RISING_OFFSET)
#define TIMER_PRESCALER_EXTERNAL_FALLING(x) ((uint64_t) x << TIMER_PRESCALER_EXTERNAL_FALLING_OFFSET)

#define TIMER_FLAG_PWM_ENABLED ((uint64_t) 1 << 0)
#define TIMER_FLAG_PWM_DISABLED ((uint64_t) 0 << 0)
#define TIMER_FLAG_8_BITS ((uint64_t) 0 << 1)
#define TIMER_FLAG_16_BITS ((uint64_t) 1 << 1)

#endif