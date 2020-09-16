// Other Functios / Tools
#include "src/functions.h"



// Help Variable for deleting the last files
long delete_previusTime = 0, delete_wait=10800000; // wait == 3 hours


void setup() {

    // Serial Setup
    Serial.begin(115200);
    while (!Serial);

    // Setup Wifi
    setup_wifi();

    // Setup Camera
    setup_cam();
     
    // Setup Web Server
    setupServer();

    
}


void loop() {

  // Delete the last month files
  if (millis() - delete_previusTime >= delete_wait) {
    delete_previusTime = millis();
    delete_last_month();
  }

  // Reconnect wifi if needed
  reconnect_if_needed_Wifi();

  // Start the server
  start_server();

}
