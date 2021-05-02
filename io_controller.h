#ifndef IO_CONTROLLER_H_
#define IO_CONTROLLER_H_

#include <Arduino.h>

#include "io_midi_serial.h"

byte current_channel = 1;

void setCurrentChannel(byte value) {
    current_channel = (int)(value / 8) + 1;
}

void controllerNoteOn(byte note, byte velocity) {
    midiSerialNoteOn(note, velocity, current_channel);
}

// but here we might save the channel when the note was pressed
// cause it would possible to change the channel while note is pressed
void controllerNoteOff(byte note, byte velocity) {
    midiSerialNoteOff(note, velocity, current_channel);
}

#endif