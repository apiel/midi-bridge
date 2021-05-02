#ifndef IO_MIDI_SERIAL_H_
#define IO_MIDI_SERIAL_H_

#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial6, MIDI);

void midiSerialInit() {
    MIDI.begin(MIDI_CHANNEL_OMNI);
}

#endif
