#ifndef IO_CONTROLLER_H_
#define IO_CONTROLLER_H_

#include <Arduino.h>

#include "Controller.h"
#include "io_controller_storage.h"
#include "io_midi_serial.h"
#include "io_util.h"

enum { VIEW_MAIN, VIEW_EDIT_CONTROLLER, VIEW_EDIT_CHANNEL, VIEW_COUNT };

byte current_pattern = 0;
byte current_view = VIEW_MAIN;
byte current_channel = 0;
byte last_control = 0;
byte note_off_channel[128];

void setCurrentChannel(byte value) { current_channel = (int)(value / (127.0 / 16.0)); }

void controllerNoteOn(byte note, byte velocity, byte channel) {
    if (current_channel) {
        channel = current_channel;
    }
    note_off_channel[note] = channel;
    midiSerialNoteOn(note, velocity, channel);
}

void controllerNoteOff(byte note, byte velocity) {
    midiSerialNoteOff(note, velocity, note_off_channel[note]);
}

void controllerCC(byte control, byte value, byte channel) {
    last_control = control;
    if (controllers[control].channel) {
        channel = controllers[control].channel;
    }
    if (current_view == VIEW_EDIT_CONTROLLER) {
        controllers[control].setControl(value);
        saveControllerProject(current_project);
    } else if (current_view == VIEW_EDIT_CHANNEL) {
        controllers[control].setChannel(value);
        saveControllerProject(current_project);
    } else if (controllers[control].control == CTRL_SEL_CHANNEL) {
        setCurrentChannel(value);
    } else if (controllers[control].control == CTRL_SEL_PATTERN) {
        midiSerialProgramChange(value, channel);
        current_pattern = value;
    } else {
        controllers[control].value = value;
        midiSerialCC(controllers[control].control, value, channel);
    }
}

void controllerProgramChange(byte program) {
    if (program == 7) {
        current_view = mod(current_view + 1, VIEW_COUNT);
    } else if (program == 6) {
        current_pattern++;
        // channel 1
        midiSerialProgramChange(current_pattern, 1);
    } else if (program < CONTROLLER_PROJECT_COUNT) {
        current_project = program;
        loadControllerProject(program);
    }
}

#endif