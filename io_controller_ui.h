#ifndef IO_CONTROLLER_UI_H_
#define IO_CONTROLLER_UI_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#include "io_controller.h"

void displayMainView(Adafruit_SSD1306* d) {
    d->setTextSize(4);
    d->printf("ch.%d\n", current_channel);
    d->setTextSize(1);

    if (controllers[last_control].control) {
        d->setCursor(0, 40);
        d->setTextSize(2);
        d->print(controllers[last_control].value);
        d->setTextSize(1);
        d->setCursor(40, 40);
        d->printf("ch.%d", controllers[last_control].channel);
        d->setCursor(40, 48);
        d->print(controllers[last_control].controlName);
    }
}

void displayEdit(Adafruit_SSD1306* d) {
    d->setTextSize(2);
    d->println("Edit\n");
    d->setTextSize(1);

    if (current_view == VIEW_EDIT_CONTROLLER) {
        d->fillRect(0, 28, 4, 8, WHITE);
    } else if (current_view == VIEW_EDIT_CHANNEL) {
        d->fillRect(0, 40, 4, 8, WHITE);
    }

    d->setCursor(8, 28);
    d->print(controllers[last_control].controlName);

    d->setCursor(8, 40);
    d->printf("Channel %d\n", controllers[last_control].channel);
}

void displayControllerUI(Adafruit_SSD1306* d) {
    d->clearDisplay();
    d->setCursor(0, 0);

    if (current_view == VIEW_MAIN) {
        displayMainView(d);
    } else {
        displayEdit(d);
    }
}

#endif