//
//  step_fast.c
//  PiStepper
//
//  Created by Maxthon Chan on 5/21/14.
//  Copyright (c) 2014 Maxthon Chan. All rights reserved.
//

#include "step_fast.h"

#include <wiringPi.h>

void step_mode_fast_set_phases(step_motor_t motor)
{
    int phase = motor->status;
    
    foreach(int, idx, motor->phase_count)
    {
        digitalWrite(motor->phases[idx], idx == phase);
    }
}

const struct step_mode _step_mode_fast = {1, step_mode_fast_set_phases};
