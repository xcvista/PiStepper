//
//  step_full.c
//  PiStepper
//
//  Created by Maxthon Chan on 5/21/14.
//  Copyright (c) 2014 Maxthon Chan. All rights reserved.
//

#include "step_full.h"

#include <wiringPi.h>

void step_mode_full_set_phases(step_motor_t motor)
{
    int phase = motor->status;
    int phase2 = (phase + 1) % motor->phase_count;
    
    foreach(int, idx, motor->phase_count)
    {
        digitalWrite(motor->phases[idx], idx == phase || idx == phase2);
    }
}

const struct step_mode _step_mode_full = {1, step_mode_full_set_phases};
