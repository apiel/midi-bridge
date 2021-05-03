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
byte note_off_channel[128];

void setCurrentChannel(byte value) { current_channel = (int)(value / 8) + 1; }

void controllerNoteOn(byte note, byte velocity) {
    note_off_channel[note] = current_channel;
    midiSerialNoteOn(note, velocity, current_channel);
}

void controllerNoteOff(byte note, byte velocity) {
    midiSerialNoteOff(note, velocity, note_off_channel[note]);
}

void controllerCC(byte control, byte value) {
    last_control = control;
    if (current_view == VIEW_EDIT_CONTROLLER) {
        controllers[control].setControl(value);
    } else if (current_view == VIEW_EDIT_CHANNEL) {
        controllers[control].setChannel(value);
    } else if (controllers[control].control == 0) {
        setCurrentChannel(value);
    } else {
        controllers[control].value = value;
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