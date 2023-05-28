#include "includes.hpp"

std::set<String> ssid_set;
std::list<String> ssid_list;

std::list<String> convert_set_to_list(std::set<String> s){

  std::list<String> List(s.begin(), s.end());

  return List;

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


void setup() {
#ifdef DEBUG_MODE
  Serial.begin(115200);
#endif

  bool res = init_station();

  bool result = ssid_scan();

  ssid_list = convert_set_to_list(ssid_set);

  return;
};


void loop() {


  delay(5000);
 
};

