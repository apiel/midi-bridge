#ifndef IO_CONTROLLER_STORAGE_H_
#define IO_CONTROLLER_STORAGE_H_

#include <SD.h>

#include "Controller.h"
#include "io_storage.h"

#define CONTROLLER_PROJECT_COUNT 6
// number of encoder/pot available --> should it be renamed?
#define CONTROLLER_COUNT 127

Controller controllers[CONTROLLER_PROJECT_COUNT][CONTROLLER_COUNT];

void setControllerProjectPath(byte project) {
    setFilePath("midibridge/%03d.io", project);
}

void loadControllerProject(byte project) {
    Serial.println("load controller project.");
    setControllerProjectPath(project);
    // Serial.printf("pattern file: %s\n", patternPath);
    if (sdAvailable && SD.exists(filePath)) {
        File file = SD.open(filePath);
        if (file) {
            while (file.available() && assignStorageValues(&file)) {
                // patterns[patternPos].add(
                //     (byte)storageValues[0], (byte)storageValues[1],
                //     (byte)storageValues[2], (byte)storageValues[3],
                //     i2b(storageValues[4]));
            }
            file.close();
            return;
        }
    }
    Serial.println("No file found.");
}

bool saveControllerProject(byte project) {
    Serial.println("load controller project.");
    if (sdAvailable) {
        setControllerProjectPath(project);
        // SD.remove(patternPath);
        File file = SD.open(filePath, FILE_WRITE);

        if (file) {
            file.seek(0);
            for (byte pos = 0; pos < CONTROLLER_COUNT; pos++) {
                // Step* step = &patterns[patternPos].steps[pos];
                // sprintf(storageBuffer, "%d %d %d %d %d\n", (int)pos,
                //         (int)step->note, (int)step->duration,
                //         (int)step->velocity, b2i(step->tie));
                // file.print(storageBuffer);
            }
            file.close();
            return true;
        }
    }
    Serial.println("Failed to open file for writing");
    return false;
}

void controllerStorageInit() {
    loadControllerProject(0);
}

#endif
