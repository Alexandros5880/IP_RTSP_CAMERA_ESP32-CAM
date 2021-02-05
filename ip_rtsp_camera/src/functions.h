#include <Arduino.h>

// Settings
#include "../settings.h"

// WiFi
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>

// Date Time
#include "time.h"

// CAM
#include "cam/OV2640.h"

// RTSP
#include "rtsp/SimStreamer.h"
#include "rtsp/OV2640Streamer.h"
#include "rtsp/CRtspSession.h"

// SD
#include "sd/SD.h"

// Get the pins for this camera
#include "../camera_pins.h"


// If RTSP Server
#ifdef ENABLE_RTSPSERVER
#include "../rtsp_settings.h"
#endif



// HostPot
#include "SPIFFS.h"
#include "hotspot_lib/ESPAsyncWebServer.h"


const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Controll Center</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
    <style>

      </style>
  </head>
  <body>
      <label for="ssid"><p style="font-size: 21px;">WIFI SSID:</p></label>
      <input type="Text" style="font-size: 21px;" id="ssid" name="ssid" />
      <br/><br/>
      <label for="password"><p style="font-size: 21px;">Password:</p></label>
      <input type="Text" style="font-size: 21px;" id="password" name="password" />
      <br/><br/>
      <label for="username"><p style="font-size: 21px;">Username:</p></label>
      <input type="Text" style="font-size: 21px;" id="username" name="username" />
      <br/><br/>
      <label for="password_u"><p style="font-size: 21px;">Password:</p></label>
      <input type="Text" style="font-size: 21px;" id="password_u" name="password_u" />
      <br/><br/>
      <br/>
      <div>
        <button id="save_button" style="font-size: 21px; border-radius: 15%;" name="save" onclick="SaveRequest()">Save</button>
        <script>
          function SaveRequest() {
            let ssid = document.getElementById("ssid").value;
            let password = document.getElementById("password").value;
            let username = document.getElementById("username").value;
            let password_u = document.getElementById("password_u").value;
            var url = "/save?ssid="+ssid+"&password="+password+"&username="+username+"&password_u="+password_u; // http://192.168.1.1:80
            var client = new XMLHttpRequest();
            client.open("GET", url, true);
            client.send(null); 
          }
        </script>
      </div>
      <br/><br/>
      <br/>
  </body>
</html>
)rawliteral";


/*          FUNCTIONS            */
// HostPot
void start_hostpot();
// Setup WiFi
void setupWIFI(String ssid, String password);
// Setup Camera
void setup_cam();
// Setup WEB SERVER
void setupServer();
// Start Server Function
void start_server();
// Real Time Delay
void _delay(int m);
// Return Date Time
String get_date_time();
// Create a bufer with the write frame rate
//void get_frames_per_fps(OV2640 * _buffer, const int &fps);  //   Not Used !!!
// Save a picture
void save_picture(OV2640 * cam);




// If Web Server
#ifdef ENABLE_WEBSERVER
	// Return Video Streem
	void handle_jpg_stream(void);
	// Return A Picture
	void handle_jpg(void);
	// Error Page
	void handleNotFound();
#endif



// If RTSP Server
#ifdef ENABLE_RTSPSERVER
	// Get rstp stream
	void getRTSPstream();
#endif
