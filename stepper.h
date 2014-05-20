//
//  stepper.h
//  PiStepper
//
//  Created by Maxthon Chan on 5/21/14.
//  Copyright (c) 2014 Maxthon Chan. All rights reserved.
//

#ifndef PiStepper_stepper_h
#define PiStepper_stepper_h

#include <sys/cdefs.h>
#include <pthread.h>

#define foreach(_type, _var, _limit) for (_type _var; _var < _limit; _var++)

typedef struct step_motor *step_motor_t;
typedef const struct step_mode *step_mode_t;

__BEGIN_DECLS

step_motor_t step_motor_create(step_mode_t mode, int phase_count, ...);
step_motor_t step_motor_retain(step_motor_t motor);
void step_motor_forward(step_motor_t motor);
void step_motor_backward(step_motor_t motor);
void step_motor_release(step_motor_t motor);

__END_DECLS

struct step_motor
{
    int retain_count;
    pthread_mutex_t *retain_count_mutex;
    
    step_mode_t mode;
    int status;
    pthread_mutex_t *status_mutex;
    
    int phase_count;
    int phases[];
} __attribute__((packed));

struct step_mode
{
    int status_count;
    void (*set_phases)(step_motor_t motor);
} __attribute__((packed));

#endif
