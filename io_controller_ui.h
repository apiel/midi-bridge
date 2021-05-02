#ifndef IO_CONTROLLER_UI_H_
#define IO_CONTROLLER_UI_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#include "io_controller.h"

void displayControllerUI(Adafruit_SSD1306* d) {
    d->clearDisplay();
    d->setCursor(0, 0);

    d->setTextSize(4);
    d->printf("ch.%d\n", current_channel);
    d->setTextSize(1);
}

#endif