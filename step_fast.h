//
//  step_fast.h
//  PiStepper
//
//  Created by Maxthon Chan on 5/21/14.
//  Copyright (c) 2014 Maxthon Chan. All rights reserved.
//

#ifndef PiStepper_step_fast_h
#define PiStepper_step_fast_h

#include "stepper.h"

__BEGIN_DECLS

const struct step_mode _step_mode_fast;

__END_DECLS

#define step_mode_fast (&_step_mode_full)

#endif
