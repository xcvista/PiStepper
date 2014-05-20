//
//  digitalWrite.c
//  PiStepper
//
//  Created by Maxthon Chan on 5/21/14.
//  Copyright (c) 2014 Maxthon Chan. All rights reserved.
//

#include <stdio.h>
#include <wiringPi.h>

void __attribute__((weak)) pinMode(int pin, int mode)
{
    printf("pin %d mode is %d.\n", pin, mode);
}

void __attribute__((weak)) digitalWrite(int pin, int value)
{
    printf("write pin %d to %s.\n", pin, value ? "on" : "off");
}
