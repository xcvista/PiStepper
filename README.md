# PiStepper

A simple library to drive step motors with GPIO.

## Introduction

This is a library that controls GPIO to emit phases of stepper motor signals,
using wiringPi library.

## Debug mode

This library have a weak symbol `digitalWrite` which is overlaid when linked
against wiringPi. If you avoid linking with wiringPi, the weak symbol get used
and generates debug information.

You can link this library with wiringPi to turn off this debug mode.
