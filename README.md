The video Streaming can takes photos like frames but make the video streaming slow.
You can take a photo but not with the streaming functionality.

# Setup:
	# // HTTP
	Go to settings.h and set:
	ssid = "";
	password = "";
	and next setup the ip setings
	setup the server_port
	define the right cam model
	# // RTSP
	Go to settings.h and set:
	ssid = "";
	password = "";
	define the right cam model
	make comment " #define ENABLE_WEBSERVER "
	Go to rtsp_settings.h and set:
	setup the port
	setup the url suffix
	defined the //#define ENABLE_RTSPSERVER