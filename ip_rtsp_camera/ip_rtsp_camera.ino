#include "src/functions.h"




//   rtsp://[username:password@]ip_address[:rtsp_port]/server_URL[[?param1=val1[?param2=val2]…[?paramN=valN]]




// Reconnect wifi if needed
void _connect(int num, long delay_millis) {
  if (!hostpot_run) {
    if (WiFi.status() != WL_CONNECTED) {
      String ssid = readFile(SD_MMC, "/ssid.txt");
      String password = readFile(SD_MMC, "/password.txt");
      setupWIFI(ssid, password);
      if (WiFi.status() == WL_CONNECTED) {
        setup_cam();
        setupServer();
      }
      // 5 tryies for connection
      count_reconnections++;
      if(count_reconnections == num) {
        hostpot_run = true;
        count_reconnections = 0;
      }
      delay(delay_millis);
    }
    if (WiFi.status() == WL_CONNECTED) {
      start_server();
    }
  }
  if (hostpot_run) {
    if (count_hostpot == 0) {
      // after submit hostpot resets count_reconnections = 0, count_hostpot = 0, hostpot_run = false;
      start_hostpot();
      hostpot_run = true;
      count_hostpot++;
    }
  }
}





void setup() {
    // Serial Setup
    Serial.begin(115200);
    while (!Serial);
    setup_SD();
    _connect(2,1000);
}


void loop() {
  _connect(10,10000);
}
