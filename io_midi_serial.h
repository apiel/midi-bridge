#ifndef IO_MIDI_SERIAL_H_
#define IO_MIDI_SERIAL_H_

#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial6, MIDI);

void midiSerialInit() {
    MIDI.begin(MIDI_CHANNEL_OMNI);
}

void midiSerialNoteOn(byte note, byte velocity, byte channel) {
    MIDI.sendNoteOn(note, velocity, channel);
}

void midiSerialNoteOff(byte note, byte velocity, byte channel) {
    MIDI.sendNoteOff(note, velocity, channel);
}

void midiSerialCC(byte controlNumber, byte value, byte channel) {
    MIDI.sendControlChange(controlNumber, value, channel);
}

void midiSerialProgramChange(byte value, byte channel) {
    MIDI.sendProgramChange(value, channel);
}

#endif
