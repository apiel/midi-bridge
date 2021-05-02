#ifndef IO_SYNTH_H_
#define IO_SYNTH_H_

#include <Arduino.h>

#include "io_display.h"
#include "io_midi.h"

void ioInit() {
    // // to comment out
    // while (!Serial)
    //     ;

    Serial.println("Init controller");
    displayInit();

    midiInit();
    displayUpdate();
    // initStateOnMidiController();
}

unsigned long last_time = millis();
void ioLoop() {
    midiLoop();
    displayLoop();
}

#endif
