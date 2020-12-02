//#pragma once  // Include this file only ones

static const char* ssid = "WIND_2.4G_E9E03F";
static const char* password = "DYk9RCbdEZ";


// Variable to store the Ip
#define IP
#ifdef IP
static IPAddress ip(192, 168, 1, 33);
// Set your Gateway IP address
static IPAddress gateway(192, 168, 1, 254); // Routers IP
static IPAddress subnet(255, 255, 255, 0);
#else
static IPAddress ip;
#endif


static int server_port = 152;
static String server_username = "alexandrosplatanios";
static String server_password = "Platanios719791";


static String img_path = "/Images";


/*               Select camera model                   */

//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE
#define CAMERA_MODEL_AI_THINKER

/*               Select type of server                 */
#define ENABLE_WEBSERVER    // WEB SERVER
