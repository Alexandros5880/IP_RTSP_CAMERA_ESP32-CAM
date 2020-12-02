#include "functions.h"




// For Video Frames
static OV2640 cam;

// Variable to store the Ip
static IPAddress ip;





// If Web Server
#ifdef ENABLE_WEBSERVER

  // Create Server Object
  static WebServer server(server_port);

  // Return Video Streem
  void handle_jpg_stream(void) {
    // Get the parametres
    String rec = server.arg("rec");
    WiFiClient client = server.client();
    String response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
    server.sendContent(response);
    while (1) {
      cam.run();
      if ( ! client.connected() ) {
          break;
      }
      response = "--frame\r\n";
      response += "Content-Type: image/jpeg\r\n\r\n";
      server.sendContent(response);
      // Real Time size and buffer
      int _size = cam.getSize();
      uint8_t * frame = (uint8_t *) cam.getfb();
      // Servers response frames
      client.write(frame, _size);  // Return Cam Frames
      //Serial.println(response);                             /////
      server.sendContent("\r\n");
      if (!client.connected())
            break;
      // Recording
      if (rec == "true") {
        recording(&cam);
        //save_picture(&cam);
      }
      // Reconnect wifi if needed
      reconnect_if_needed_Wifi();
    }
  }
  
  // Return A Picture
  void handle_jpg(void) {
      WiFiClient client = server.client();
      if ( ! client.connected() ) {
          return;
      }
      // Camera Run
      cam.run();
      String response = "HTTP/1.1 200 OK\r\n";
      response += "Content-disposition: inline; filename=capture.jpg\r\n";
      response += "Content-type: image/jpeg\r\n\r\n";
      server.sendContent(response);
      // Saving to file
      save_picture(&cam);
      // Get image Buffer and length
      int _size = cam.getSize();
      const uint8_t * frame = cam.getfb();
      // Show to page on server
      client.write(frame, _size);  // Return Cam Frames
  }
  
  // Error Page
  void handleNotFound() {
      String message = "Server is running!\n\n";
      message += "URI: ";
      message += server.uri();
      message += "\nMethod: ";
      message += (server.method() == HTTP_GET) ? "GET" : "POST";
      message += "\nArguments: ";
      message += server.args();
      message += "\n";
      server.send(200, "text/plain", message);
  }
  
#endif





// If RTSP Server
#ifdef ENABLE_RTSPSERVER

  static WiFiServer rtspServer(rtsp_port);
  static CStreamer *streamer;
  static CRtspSession *session;
  static WiFiClient client; // FIXME, support multiple clients
  
  // Get rstp stream
  void getRTSPstream() {  // Inside Loop Function
    uint32_t msecPerFrame = 6;
    static uint32_t lastimage = micros();
  
    // If we have an active client connection, just service that until gone
    // (FIXME - support multiple simultaneous clients)
    if (session) {
        session->handleRequests(0); // we don't use a timeout here,
        // instead we send only if we have new enough frames
        uint32_t now = micros();
        if(now > lastimage + msecPerFrame || now < lastimage) { // handle clock rollover
            session->broadcastCurrentFrame(now);
            lastimage = now;
  
            // check if we are overrunning our max frame rate
            now = millis();
            if(now > lastimage + msecPerFrame)
                printf("warning exceeding max frame rate of %d ms\n", now - lastimage);
        }
        if(session->m_stopped) {
            delete session;
            delete streamer;
            session = NULL;
            streamer = NULL;
        }
    } else {
        client = rtspServer.accept();
        if(client) {
            //streamer = new SimStreamer(&client, true);             // our streamer for UDP/TCP based RTP transport
            streamer = new OV2640Streamer(&client, cam);             // our streamer for UDP/TCP based RTP transport
            session = new CRtspSession(&client, streamer);           // our threads RTSP session and state
        }
    }
    
  }
#endif






// Setup Wifi
void setup_wifi() {
    // WiFi Connect
    //WiFi.config(ip);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(F("."));
    }
    ip = WiFi.localIP();
    Serial.println(F("WiFi connected"));
    Serial.print("AP MAC: ");
    Serial.println(WiFi.softAPmacAddress());
}





// Reconnect wifi if needed
void reconnect_if_needed_Wifi() {
  //WiFi.config(ip);
  if ( WiFi.status() != WL_CONNECTED ) {
    WiFi.begin(ssid, password); // Wifi Connect
    //WiFi.config(ip, gateway, subnet);
    while (WiFi.status() != WL_CONNECTED) {
      delay(300);
      Serial.print(".");
    }
    // Setup Web Server
    setupServer();
  }
}





// Setup Camera
void setup_cam() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  if( psramFound() ){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  #if defined(CAMERA_MODEL_ESP_EYE)
    pinMode(13, INPUT_PULLUP);
    pinMode(14, INPUT_PULLUP);
  #endif
  cam.init(config);
}





// Setup WEB SERVER
void setupServer() {
    #ifdef ENABLE_WEBSERVER
        Serial.println("\n\n\n\nWEB SERVER\n\n\n\n");
        server.on("/", HTTP_GET, handle_jpg_stream);
        server.on("/jpg", HTTP_GET, handle_jpg);
        server.onNotFound(handleNotFound);
        server.begin();
        Serial.print("Video Stream:  http://");
        Serial.print(ip);
        Serial.println(":"+String(server_port)+String("/")+"?rec=false");
        Serial.println("");
        Serial.print("Picture:  http://");
        Serial.print(ip);
        Serial.println(":"+String(server_port)+String("/jpg"));
        Serial.println("");
        Serial.print("Recording:  http://");
        Serial.print(ip);
        Serial.println(":"+String(server_port)+String("/recorder")+"?rec=true");
        Serial.println("");
    #endif

    // RTSP
    #ifdef ENABLE_RTSPSERVER
        Serial.println("\n\n\n\nRTSP\n\n\n\n");
        rtspServer.begin();
        Serial.print("Stream Link: rtsp://");
        Serial.print(ip);
        Serial.println( ":" + String(rtsp_port) + "/" + url_end);
        Serial.println("");
    #endif
}





// Enable the Server
void start_server() {
  // Web Server
  #ifdef ENABLE_WEBSERVER
    server.handleClient();
  #endif
  // Get RTSP Stream
  #ifdef ENABLE_RTSPSERVER
    getRTSPstream();
  #endif
}





// Real Time Delay
void _delay(int m) {
  unsigned long wait = millis()+m;
  while(millis() < wait);
}





// Return Date Time
String get_date_time() {
  // daylightOffset_sec
  //GMT +1 = 3600 sec
  //GMT +2 = 7200 sec
  //GMT +3 = 10800 sec = greece
  const char* ntpServer = "pool.ntp.org";
  const long  gmtOffset_sec = 0;
  const int   daylightOffset_sec = 10800;
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return "";
  }
  char data[100];
  strftime(data, 100, "%d-%B-%Y&%Hh-%Mm", &timeinfo);
  return String( data );  // 24-September-2020&18h-07m
}





// Create a bufer with the write frame rate                  Not Used   !!!
void get_frames_per_fps(OV2640 * _buffer, const int &fps) {
  // Xfps per second , Xhz,  X frame pes 1000 millis
  int _millis = 1000;
  int wait = (int) 1000/fps;
  for (uint8_t i = 0; i < fps; i++) {
    _buffer[i] = cam;
    _delay(wait);
  }
}





// Save a picture
void save_picture(OV2640 * cam) {
  String * folder_name = &img_path;
  camera_fb_t * fb = cam->getThis();
  setup_SD();
  createDir(SD_MMC, folder_name->c_str());
  String date = get_date_time(); // 24-September-2020&18h-07m
  // Create dir with name date and subdir with name time
  String _date = date.substring(0, date.indexOf("&"));
  String folder_path = *folder_name + "/" + _date;
  char folder_char[ folder_path.length()+1 ];
  folder_path.toCharArray(folder_char, sizeof(folder_char));
  createDir(SD_MMC, folder_char);
  Serial.println( "Created: " + folder_path );
  String _time = date.substring(date.indexOf("&")+1, date.length());
  String file = folder_path + "/" + _time + ".jpeg";
  char file_path[ file.length()+1 ];
  file.toCharArray(file_path, sizeof(file_path));
  writeFile(SD_MMC, file_path, fb);
}





// Delete files lost month every fifhteen
void delete_last_month() {
  setup_SD();
  // Find the last month date
  String date = get_date_time(); // 24-September-2020&18h-07m
  String day = date.substring(0, 2);
  String month = date.substring(3, 12);
  String year = date.substring(13, 17);
  // Find one year back
  int y = year.toInt();
  y = y-1;
  if (y <= 10) {
    year = "0"+String(y);
  } else {    
  year = String(y);
  }
  if (day == delete_scheduled_day) {  //  ../settings.h
    String last_month_folder_videos = video_path + "/" + year + "-" + month + "-" + day;
    String last_month_folder_images = img_path + "/" + year + "-" + month + "-" + day;
    removeDir(SD_MMC, last_month_folder_videos.c_str());
    removeDir(SD_MMC, last_month_folder_images.c_str());
  }
}




// Recording the Video    doesn't works  !!!
void recording(OV2640 * cam) {
  // create an mp4 content and save the video frames
  /*
  String * folder_name = &video_path;
  camera_fb_t * fb = cam->getThis();
  setup_SD();
  createDir(SD_MMC, folder_name->c_str());
  String _data = get_date_time();
  String _date = _data.substring(0, _data.indexOf("&"));
  String folder_path = *folder_name + "/" + _date;
  char folder_char[ folder_path.length()+1 ];
  folder_path.toCharArray(folder_char, sizeof(folder_char));
  createDir(SD_MMC, folder_char);
  String _time = _data.substring(_data.indexOf("&")+1, _data.length()-4);
  String file = folder_path + "/" + _time + "0.mp4";
  char file_path[ file.length()+1 ];
  file.toCharArray(file_path, sizeof(file_path));
  appendFile(SD_MMC, file_path, fb);
  */
}