# Setup:

### - HTTP
Go to settings.h and set:

    static const char* ssid = "";
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
    
    static int server_port = xxx;
    static String server_username = "username";
    static String server_password = "password";
    
    static String img_path = "/Images";
    
    
    /*               Select camera model                   */
    
    //#define CAMERA_MODEL_WROVER_KIT
    //#define CAMERA_MODEL_ESP_EYE
    //#define CAMERA_MODEL_M5STACK_PSRAM
    //#define CAMERA_MODEL_M5STACK_WIDE
    #define CAMERA_MODEL_AI_THINKER
    
    /*               Select type of server                 */
    #define ENABLE_WEBSERVER    // WEB SERVER

### - RTSP
Go to settings.h and set:

    static const char* ssid = "";
    static const char* password = "";
    
Make comment:

    #define ENABLE_WEBSERVER    // WEB SERVER

Go to rtsp_settings.h and set: Setup:

    static int rtsp_port = xxx;
    static String url_end = "mjpeg/2";  // RTSP
    
Enable:

    //#define ENABLE_RTSPSERVER   // RTSP