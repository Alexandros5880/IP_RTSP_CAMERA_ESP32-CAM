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





/*          FUNCTIONS            */
// Setup WiFi
void setupWIFI();
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
