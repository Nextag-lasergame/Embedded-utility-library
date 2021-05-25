//
// Created by timti on 25/05/2021.
//

#ifndef EMBEDDED_UTILITY_LIBRARY_DELAY_H
#define EMBEDDED_UTILITY_LIBRARY_DELAY_H

#ifdef __cplusplus
{
#endif

#ifndef F_CPU
#warning F_CPU is not defined, defining F_CPU as 1000000L
#define F_CPU 1000000L
#endif

void delay_ms(double ms);

#ifdef __cplusplus
};
#endif

#endif //EMBEDDED_UTILITY_LIBRARY_DELAY_H
