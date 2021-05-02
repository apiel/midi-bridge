#ifndef IO_CONTROLLER_H_
#define IO_CONTROLLER_H_

#include <Arduino.h>

byte current_channel = 1;

void setCurrentChannel(byte value) {
    current_channel = (int)(value / 8) + 1;
}

#endif