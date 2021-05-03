#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <Arduino.h>

#include "io_util.h"

typedef struct {
    byte control;
    const char* name;
} Controls;

Controls controls[] = {
    {0, "Sel. channel"},      {7, "Level"},      {10, "Pan"},
    {71, "Resonance"},        {74, "Cutoff"},    {83, "Filter EG"},
    {72, "EG Delay/Release"}, {73, "EG Attack"}, {80, "Osc. Pitch"},
    {81, "Osc. Glide"},       {82, "Osc. Edit"}, {85, "Mod. Depth"},
    {86, "Mod. Speed"},
};

#define CONTROL_COUNT sizeof controls / sizeof controls[0]

class Controller {
   public:
    byte channel = 1;
    byte controlSel = 0;
    byte control = controls[0].control;
    const char* controlName = controls[0].name;

    void setChannel(byte value) { channel = (int)(value / 8) + 1; }
    void setControl(byte value) {
        controlSel = (int)(value / (127 / CONTROL_COUNT));
        control = controls[controlSel].control;
        controlName = controls[controlSel].name;
    }
};

#endif
