#include "Arduino.h"
#include "FS.h" 
#include "SD_MMC.h" 
#include "esp_camera.h"


// Setup SD
void setup_SD();

// List dir in SD card
void listDir(fs::FS &fs, const char * dirname, uint8_t levels);

// Create a dir in SD card
void createDir(fs::FS &fs, const char * path);

// Delete a dir in SD card
void removeDir(fs::FS &fs, const char * path);

// Read a file in SD card
String readFile(fs::FS &fs, const char * path);

// Write a file in SD card
void writeFile(fs::FS &fs, const char * path, const char * message);

// Write a file in SD card
void writeFilePic(fs::FS &fs, const char * path, camera_fb_t * fb);

// Append to the end of file in SD card
void appendFile(fs::FS &fs, const char * path, const char * message);

// Append to the end of file in SD card
void appendFile(fs::FS &fs, const char * path, camera_fb_t * fb);

// Rename a file in SD card
void renameFilePic(fs::FS &fs, const char * path1, const char * path2);

// Delete a file in SD card
void deleteFile(fs::FS &fs, const char * path);

// Test read and write speed using test.txt file
void testFileIO(fs::FS &fs, const char * path);



/*
    listDir(SD_MMC, "/", 0);
    createDir(SD_MMC, "/mydir");
    listDir(SD_MMC, "/", 0);
    removeDir(SD_MMC, "/mydir");
    listDir(SD_MMC, "/", 2);
    writeFile(SD_MMC, "/hello.txt", "Hello ");
    appendFile(SD_MMC, "/hello.txt", "World!\n");
    readFile(SD_MMC, "/hello.txt");
    deleteFile(SD_MMC, "/foo.txt");
    renameFile(SD_MMC, "/hello.txt", "/foo.txt");
    readFile(SD_MMC, "/foo.txt");
    testFileIO(SD_MMC, "/test.txt");
    Serial.printf("Total space: %lluMB\n", SD_MMC.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD_MMC.usedBytes() / (1024 * 1024));  
*/
