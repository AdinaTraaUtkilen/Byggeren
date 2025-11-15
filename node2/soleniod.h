#pragma once


#include "startcode/time.h"
#include "startcode/can.h"
#include "sam/sam3x/include/sam.h"

void soleniod_init();


void run_soleniod(CanMsg *message);