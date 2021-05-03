#ifndef IO_CONTROLLER_H_
#define IO_CONTROLLER_H_

#include <Arduino.h>

#include "Controller.h"
#include "io_midi_serial.h"
#include "io_util.h"

enum { VIEW_MAIN, VIEW_EDIT_CONTROLLER, VIEW_EDIT_CHANNEL, VIEW_COUNT };

Controller controllers[127];

byte current_view = VIEW_MAIN;
byte current_channel = 1;
byte last_control = 0;

void setCurrentChannel(byte value) { current_channel = (int)(value / 8) + 1; }

void controllerNoteOn(byte note, byte velocity) {
    midiSerialNoteOn(note, velocity, current_channel);
}

// but here we might save the channel when the note was pressed
// cause it would possible to change the channel while note is pressed
void controllerNoteOff(byte note, byte velocity) {
    midiSerialNoteOff(note, velocity, current_channel);
}

void controllerCC(byte control, byte value) {
    last_control = control;
    if (current_view == VIEW_EDIT_CONTROLLER) {
        controllers[control].setControl(value);
    } else if (current_view == VIEW_EDIT_CHANNEL) {
        controllers[control].setChannel(value);
    } else {
        midiSerialCC(controllers[control].control, value,
                     controllers[control].channel);
    }
}

void controllerProgramChange(byte program) {
    if (program == 7) {
        current_view = mod(current_view + 1, VIEW_COUNT);
    }
}

#endif