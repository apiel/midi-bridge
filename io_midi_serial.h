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

#endif
