#pragma once

#include "avr/io.h"
#include "avr/interrupt.h"
#include "stdio.h"
#include "global.h"
#include "adc.h"


void init_interrupt();

ISR(INT2_vect);



