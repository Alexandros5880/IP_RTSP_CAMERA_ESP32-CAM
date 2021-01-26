//#pragma once  // Include this file only ones

// WIFI
/*
static const char* ssid = "WIND_2.4G_E9E03F";
static const char* password = "DYk9RCbdEZ";
*/


// HOSTPOT
static const char* ssid_h     = "ESP32-Access-Point";
static const char* password_h = "123456789";
static IPAddress Ip_h(192, 168, 1, 1);
static IPAddress NMask_h(255, 255, 255, 0);


// Variable to store the Ip
#define IP
#ifdef IP
static IPAddress ip(192, 168, 1, 11);
// Set your Gateway IP address
static IPAddress gateway(192, 168, 1, 254); // Routers IP
static IPAddress subnet(255, 255, 255, 0);
#else
static IPAddress ip;
#endif



static int server_port = 155;
static String server_username = "alexandrosplatanios";
static String server_password = "Platanios719791";


static String url_end_s = "/stream";
static String img_path = "/Pic";



/*               Select camera model                   */

//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE
#define CAMERA_MODEL_AI_THINKER

/*               Select type of server                 */
#define ENABLE_WEBSERVER    // WEB SERVER




// Dont change this
static int count_reconnections = 0, count_hostpot = 0;
static boolean hostpot_run = false;
