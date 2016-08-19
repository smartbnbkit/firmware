#include "Configuration.hpp"

Configuration config;

void setup() {
    Serial.begin(115200);
    config.begin("SmartBnbKit", "toptal");
}

void loop() {
    
}