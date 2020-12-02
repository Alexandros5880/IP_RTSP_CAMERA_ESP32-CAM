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


/*
// Thread
#include <Thread.h>

// Example
Thread web_server = Thread();
web_server.onRun(handle_jpg_stream);
if(web_server.shouldRun()) {
  web_server.run();
}
*/







/*          FUNCTIONS            */

// Setup Wifi
void setup_wifi();
// Reconnect wifi if needed
void reconnect_if_needed_Wifi();
// Setup WEB SERVER
void setupServer();
// Setup Camera
void setup_cam();
// Start Server Function
void start_server();
// Real Time Delay
void _delay(int m);
// Return Date Time
String get_date_time();
// Save a picture
void save_picture(OV2640 * cam);
// Recording the Video
void recording(OV2640 * cam);  //  Doesn't Works !!!
// Delete Files Last Month
void delete_last_month();
// Create a bufer with the write frame rate
void get_frames_per_fps(OV2640 * _buffer, const int &fps);  //   Not Used !!!




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
