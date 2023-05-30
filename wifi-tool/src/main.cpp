#include "includes.hpp"

std::set<String> ssid_set;
std::list<String> ssid_list;

// Setup mode variables
ESP8266WebServer server(80);

std::list<String> convert_set_to_list(std::set<String> s){

  std::list<String> List(s.begin(), s.end());

  return List;

};

void on_request_webpage(void){

  delay(3000);

  File root_webpage = LittleFS.open("/fs/webpage.html", "r");

  if (!root_webpage) {
    DEBUG_PRINT("LittleFS::open() failed...\n");
    server.send(404, "text/plain", "File not found");
  } else {
    String webpage_content = root_webpage.readString();
    server.send(200, "text/html", webpage_content);
    root_webpage.close();
  };


};

bool ssid_scan(void){

  delay(2000);
  DEBUG_PRINT("Scan start ... \n");
  int num_networks = WiFi.scanNetworks(false, true);

  DEBUG_PRINT("%d network(s) found\n", num_networks);

  if (!num_networks) {return false;}

  for (int i = 0; i < num_networks; i++)
  {
    ssid_set.insert(WiFi.SSID(i));
    DEBUG_PRINT("%s \n", WiFi.SSID(i).c_str());
  }

  return true;
  
};


bool init_station(void){

  bool result = false;
  result = WiFi.mode(WIFI_STA);

  if (!result){
    DEBUG_PRINT("ERROR ESTABLISHING STATION...\n");
    return false;
  };

  WiFi.disconnect();
  delay(100);

  return true;

};

bool init_ap(void){

  delay(3000);
  // likely will want to make these parameters specifiable
  if (!WiFi.softAPConfig(IPAddress(192, 168, 0, 1), IPAddress(192, 168, 0, 0), IPAddress(255, 255, 255, 0))) {
    DEBUG_PRINT("Failed to configure server!\n");
    return false;
  };

  String ap_ssid = "test-access-pt";
  String ap_password = "password";

  bool ap_created = WiFi.softAP(ap_ssid, ap_password); 

  if (!ap_created) {
    DEBUG_PRINT("Failed to create server!\n");
    return false;
  };

  IPAddress ip = WiFi.softAPIP();
  DEBUG_PRINT("AP IP address: %s\n", ip.toString().c_str());

  server.on("/", on_request_webpage);
  server.onNotFound(on_request_webpage);
  server.begin();

  DEBUG_PRINT("HTTP server started\n");
  return true;

};


void setup() {
#ifdef DEBUG_MODE
  Serial.begin(115200);
#endif

  if (!LittleFS.begin()) {
    DEBUG_PRINT("LittleFS::begin() failed...\n");
  };

  //bool res = init_station();

  bool r1 = init_ap();

  bool result = ssid_scan();

  ssid_list = convert_set_to_list(ssid_set);

  

  return;
};


void loop() {

  server.handleClient();

  //delay(5000);
 
};

