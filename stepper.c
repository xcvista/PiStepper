//
//  stepper.c
//  PiStepper
//
//  Created by Maxthon Chan on 5/21/14.
//  Copyright (c) 2014 Maxthon Chan. All rights reserved.
//

#include "stepper.h"

#include <stdlib.h>
#include <wiringPi.h>
#include <stdarg.h>
#include <string.h>

step_motor_t step_motor_create(step_mode_t mode, int phase_count, ...)
{
    if (!mode)
        return NULL;
    
    size_t size =
        sizeof(step_mode_t) +
        sizeof(pthread_mutex_t *) +
        sizeof(int) * (phase_count + 3);
    step_motor_t motor = malloc(size);
    if (!motor)
        return NULL;
    
    bzero(motor, size);

    motor->retain_count = 1;
    motor->retain_count_mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(motor->retain_count_mutex, NULL);
    
    motor->mode = mode;
    motor->status = 0;
    motor->status_mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(motor->status_mutex, NULL);
    
    motor->phase_count = phase_count;
    
    va_list args;
    va_start(args, phase_count);
    foreach(int, idx, phase_count)
    {
        int pin = va_arg(args, int);
        digitalWrite(pin, LOW);
        motor->phases[idx] = pin;
    }
    
    return motor;
}

step_motor_t step_motor_retain(step_motor_t motor)
{
    pthread_mutex_t *mutex = motor->retain_count_mutex;
    pthread_mutex_lock(mutex);
    
    motor->retain_count++;
    
    pthread_mutex_unlock(mutex);
    return motor;
}

void step_motor_shift(step_motor_t motor, int size)
{
    if (!size)
        return;
    
    pthread_mutex_lock(motor->status_mutex);
    
    motor->mode->set_phases(motor);
    
    int pulses = motor->mode->status_count * motor->phase_count;
    
    if (size > 0)
    {
        motor->status = (motor->status + 1) % pulses;
    }
    else
    {
        motor->status = (motor->status ?: pulses) - 1;
    }
    
    pthread_mutex_unlock(motor->status_mutex);
}

void step_motor_forward(step_motor_t motor)
{
    step_motor_shift(motor, 1);
}

void step_motor_backward(step_motor_t motor)
{
    step_motor_shift(motor, -1);
}

void step_motor_release(step_motor_t motor)
{
    pthread_mutex_t *mutex = motor->retain_count_mutex;
    pthread_mutex_lock(mutex);
    
    if (!motor->retain_count--)
    {
        pthread_mutex_lock(motor->status_mutex);
        pthread_mutex_destroy(motor->status_mutex);
        free(motor->status_mutex);
        
        free(motor);
        
        pthread_mutex_destroy(mutex);
        free(mutex);
    }
    else
    {
        pthread_mutex_unlock(mutex);
    }
}
