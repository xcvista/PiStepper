//
//  step_single.c
//  PiStepper
//
//  Created by Maxthon Chan on 5/21/14.
//  Copyright (c) 2014 Maxthon Chan. All rights reserved.
//

#include "step_half.h"

#include <wiringPi.h>

void step_mode_half_set_phases(step_motor_t motor)
{
    int phase = motor->status / 2;
    int stage = motor->status & 1;
    
    if (!stage)
    {
        foreach(int, idx, motor->phase_count)
        {
            digitalWrite(motor->phases[idx], idx == phase);
        }
    }
    else
    {
        int phase2 = (phase + 1) % motor->phase_count;
        foreach(int, idx, motor->phase_count)
        {
            digitalWrite(motor->phases[idx], idx == phase || idx == phase2);
        }
    }
}

const struct step_mode _step_mode_half = {2, step_mode_half_set_phases};
