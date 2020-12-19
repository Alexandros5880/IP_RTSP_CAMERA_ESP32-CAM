// Other Functios / Tools
#include "src/functions.h"

//   rtsp://[username:password@]ip_address[:rtsp_port]/server_URL[[?param1=val1[?param2=val2]…[?paramN=valN]]



// Reconnect wifi if needed
void _connect() {
    // WiFi Connect
  if ( WiFi.status() != WL_CONNECTED ) {
    // Setup WiFi
    setupWIFI();
    // Setup Camera
    setup_cam();
    // Setup Web Server
    setupServer();
  }
  // Start Server
  start_server();
}





void setup() {
    // Serial Setup
    Serial.begin(115200);
    while (!Serial);
    // Connect server
    _connect();    
}


void loop() {
  _connect();
}
