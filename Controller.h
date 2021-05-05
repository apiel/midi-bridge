#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <Arduino.h>

#include "io_util.h"

typedef struct {
    byte control;
    char* name;
} Controls;

enum { CTRL_SEL_CHANNEL, CTRL_SEL_PATTERN };

Controls controls[] = {
    {CTRL_SEL_CHANNEL, "Sel. channel"},
    {CTRL_SEL_PATTERN, "Sel. pattern"},
    {7, "Level"},
    {10, "Pan"},
    {71, "Resonance"},
    {74, "Cutoff"},
    {83, "Filter EG"},
    {72, "EG Delay/Release"},
    {73, "EG Attack"},
    {80, "Osc. Pitch"},
    {81, "Osc. Glide"},
    {82, "Osc. Edit"},
    {85, "Mod. Depth"},
    {86, "Mod. Speed"},
};

// #define CONTROL_COUNT sizeof controls / sizeof controls[0]
#define CONTROL_COUNT 14
#define CONTROL_DIVIDER (int)(127 / (CONTROL_COUNT - 1))

class Controller {
   public:
    byte channel = 1;
    byte controlSel = 0;
    byte control = controls[0].control;
    byte value = 0;
    char* controlName = controls[0].name;

    void set(byte _control, byte _channel) {
        control = _control;
        channel = _channel;
        assignName();
    }

    void assignName() {
        for (byte n; n < CONTROL_COUNT; n++) {
            if (control == controls[n].control) {
                controlName = controls[n].name;
                return;
            }
        }
    }

    void setChannel(byte value) { channel = (int)(value / 8) + 1; }
    void setControl(byte value) {
        controlSel = (int)(value / CONTROL_DIVIDER);
        control = controls[controlSel].control;
        controlName = controls[controlSel].name;
    }
};

#endif
