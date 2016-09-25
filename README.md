# ESPWifiServer

## Description
If you want a web server with **static ip** in you ESP8266 wifi module, you can use this arduino code. Here **GPIO2** pin of ESP8266 module(`const int pin = 2;`) is used for controlling relay or leds. For that you have to do follwing changes in the code:
* First thing is, you will have to provide your **ssid** and **wifipassword** in the code.
```cpp
const char* ssid = "mywifi";
const char* password = "password";
```
* Get your gateway(or router) and subnet, then set the desired ip according to your gateway.
```cpp
IPAddress ip(192, 168, 1, xx); // where xx is the desired IP Address
IPAddress gateway(192, 168, 1, 254); // set gateway to match your wifi network
IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your wifi network
```
* Now just use you ip, gateway and subnet to set static ip in `void setup()`.
```cpp
void setup(){
	......
	WiFi.config(ip, gateway, subnet);
	......
}
```
## Tools
You can download [ArdroidHttpClient](https://github.com/Arduino-and-RaspberryPi/ESPHttpClient/releases) to send request via HTTP. Or you can download or fork the project from [link](https://github.com/Arduino-and-RaspberryPi/ESPHttpClient.git) on **git-hub** and build **apk** using [Android Studio](https://developer.android.com/studio/index.html) and install to your android phone. You will have to provide a name(any name), your ESP8266 ip (the static ip) and port(as given in the code port is **80**). Now you can control your home appliances using the app.

### Note:
> While using this code with ESP8266 wifi module, you phone or computer should be on same network.

## Connections:
<img src="https://github.com/Arduino-and-RaspberryPi/ESPWifiServer/blob/master/ESP-12Connection.jpg" width="540" height="360" />
