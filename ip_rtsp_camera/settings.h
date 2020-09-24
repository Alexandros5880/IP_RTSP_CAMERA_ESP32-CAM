
static const char* ssid = "WIND_2.4G_E9E03F";
static const char* password = "DYk9RCbdEZ";


static int server_port = 152;
static int rtsp_port = 153;
static const char* url_stream_end = "/mjpeg/1";  // src/CRtspSession.cpp line 283-284 , 347


//int record_fps = 45;
static String video_path = "/videos";
static String img_path = "/pictures";



// What day every month delete tha last files to get free space in memmory
static String delete_scheduled_day = "1";





/*               Select camera model                   */

//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE
#define CAMERA_MODEL_AI_THINKER






/*               Select type of server                 */
#define ENABLE_WEBSERVER    // WEB SERVER
//#define ENABLE_RTSPSERVER   // RTSP
