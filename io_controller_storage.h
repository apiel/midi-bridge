#ifndef IO_CONTROLLER_STORAGE_H_
#define IO_CONTROLLER_STORAGE_H_

#include <SD.h>

#include "Controller.h"
#include "io_storage.h"

#define CONTROLLER_PROJECT_COUNT 6
// number of encoder/pot available --> should it be renamed?
#define CONTROLLER_COUNT 127

Controller controllers[CONTROLLER_COUNT];
byte current_project = 0;

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
                controllers[(byte)storageValues[0]].set((byte)storageValues[1],
                                                        (byte)storageValues[2]);
                // Serial.printf("cc %d %d %d\n", (int)storageValues[0],
                //               (int)storageValues[1], (int)storageValues[2]);
            }
            file.close();
            return;
        }
    }
    Serial.println("No file found.");
}

bool saveControllerProject(byte project) {
    Serial.println("save controller project.");
    if (sdAvailable) {
        setControllerProjectPath(project);
        // SD.remove(patternPath);
        File file = SD.open(filePath, FILE_WRITE);

        if (file) {
            file.seek(0);
            for (byte pos = 0; pos < CONTROLLER_COUNT; pos++) {
                Controller* c = &controllers[pos];
                sprintf(storageBuffer, "%d %d %d\n", (int)pos, (int)c->control,
                        (int)c->channel);
                file.print(storageBuffer);
            }
            file.close();
            return true;
        }
    }
    Serial.printf("Failed to open file for writing %s\n", filePath);
    return false;
}

void controllerStorageInit() { loadControllerProject(current_project); }

#endif
