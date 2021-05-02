#ifndef IO_MIDI_H_
#define IO_MIDI_H_

#include <Arduino.h>

#include "io_controller.h"
#include "io_display.h"
#include "io_midi_core.h"
#include "io_midi_util.h"
#include "io_midi_serial.h"

void noteOnHandler(byte channel, byte note, byte velocity) {
    Serial.print("Note On, ch=");
    Serial.print(channel, DEC);
    Serial.print(", note=");
    Serial.print(note, DEC);
    Serial.print(", velocity=");
    Serial.println(velocity, DEC);

    displayUpdate();
}

void noteOffHandler(byte channel, byte note, byte velocity) {
    Serial.print("Note Off, ch=");
    Serial.print(channel, DEC);
    Serial.print(", note=");
    Serial.print(note, DEC);
    Serial.print(", velocity=");
    Serial.println(velocity, DEC);

    displayUpdate();
}

void controlChangeHandler(byte channel, byte control, byte value) {
    byte knob = control % KNOB_COUNT;
    int8_t direction = getKnobDirection(knob, value);

    Serial.print("Control Change, ch=");
    Serial.print(channel, DEC);
    Serial.print(", control=");
    Serial.print(control, DEC);
    Serial.print(", knob=");
    Serial.print(knob, DEC);
    Serial.print(", direction=");
    Serial.print(direction, DEC);
    Serial.print(", value=");
    Serial.println(value, DEC);

    // if channel == 1
    if (control == 16) {
        setCurrentChannel(value);
    }

    displayUpdate();
}

void afterTouchPolyHandler(uint8_t channel, uint8_t note, uint8_t pressure) {
    Serial.print("AfterTouchPoly, ch=");
    Serial.print(channel, DEC);
    Serial.print(", note=");
    Serial.print(note, DEC);
    Serial.print(", pressure=");
    Serial.println(pressure, DEC);
}

void sysExHandler(const uint8_t* data, uint16_t length, bool complete) {
    Serial.println("some sysExHandler data");
}

void midiInit() {
    midiSerialInit();
    myusb.begin();
    for (byte n = 0; n < MIDI_COUNT; n++) {
        midiUsb[n].setHandleNoteOn(noteOnHandler);
        midiUsb[n].setHandleNoteOff(noteOffHandler);
        midiUsb[n].setHandleControlChange(controlChangeHandler);
        midiUsb[n].setHandleAfterTouchPoly(afterTouchPolyHandler);
        midiUsb[n].setHandleSysEx(sysExHandler);

        // Serial.print("midi ");
        // Serial.print(midi[n].idProduct());
        // if (midi[n].manufacturer() != NULL && midi[n].product() != NULL) {
        //     String make = (char*)midi[n].manufacturer();
        //     String model = (char*)midi[n].product();
        //     Serial.print(String(make) + " " + model + " ");
        // }
    }
}

void midiLoop() {
    myusb.Task();
    for (byte n = 0; n < MIDI_COUNT; n++) {
        while (midiUsb[n].read())
            ;
    }
}

#endif
