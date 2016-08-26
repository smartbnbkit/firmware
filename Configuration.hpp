#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <EEPROM.h>
#include <vector>
#include <algorithm>
#include <cstring>

#include "Resources.h"

class Configuration {
    struct __attribute__((__packed__)) APICredentials {
        uint16_t Magic{0x9c24};
        char Username[128];
        char Password[64];
    };

public:
    Configuration() {
        EEPROM.begin(sizeof(APICredentials));
        EEPROM.get(0, m_apiCredentials);
        if (m_apiCredentials.Magic != 0x9c24) {
            memset(m_apiCredentials.Username, 0, sizeof(m_apiCredentials.Username));
            memset(m_apiCredentials.Password, 0, sizeof(m_apiCredentials.Password));
            m_apiCredentials.Magic = 0x9c24;
        }
    }
    
    bool begin(const char *ssid, const char *pass = nullptr) {
        WiFi.mode(WIFI_AP);

        if (pass) WiFi.softAP(ssid, pass);
        else      WiFi.softAP(ssid);

        delay(500);

        m_dns.setErrorReplyCode(DNSReplyCode::NoError);
        m_dns.start(53, "*", WiFi.softAPIP());

        m_http.on("/", [this] {
            String page = FPSTR(Resource_Index);
            page.replace("%ssid%", WiFi.SSID());
            page.replace("%pass%", WiFi.psk());
            page.replace("%api_login%", m_apiCredentials.Username);
            page.replace("%api_pass%", m_apiCredentials.Password);
            
            m_http.send(200, "text/html", page);
        });
        m_http.on("/scan", [this] {
            String page("[");
            int n = WiFi.scanNetworks();
            if (n > 0) {
                std::vector<int> v(n);
                std::iota(v.begin(), v.end(), 0);
                std::sort(v.begin(), v.end(), [](int a, int b) -> bool { return WiFi.RSSI(a) > WiFi.RSSI(b); });
                
                for (int x : v) {
                    if (page.length() > 1) page += ',';
                    page += "{\"ssid\": \"" + WiFi.SSID(x) + "\", " +
                            " \"strength\": " + String(signalStrength(WiFi.RSSI(x))) + ", " +
                            " \"open\": " + (WiFi.encryptionType(x) == ENC_TYPE_NONE? "true" : "false") + 
                            "}";
                }
            }
            page += "]";

            m_http.send(200, "application/json", page);
        });
        m_http.on("/save", [this] {
            String ssid = m_http.arg("ssid").c_str();
            String pass = m_http.arg("password").c_str();
            String apiLogin = m_http.arg("api_login").c_str();
            String apiPass  = m_http.arg("api_pass").c_str();

            // Save to flash
            WiFi.begin(ssid.c_str(), pass.c_str());
            
            // Save API credentials
            strncpy(m_apiCredentials.Username, apiLogin.c_str(), sizeof(m_apiCredentials.Username));
            strncpy(m_apiCredentials.Password, apiPass.c_str(), sizeof(m_apiCredentials.Password));
            EEPROM.put(0, m_apiCredentials);
            EEPROM.commit();

            m_http.send(200, "text/plain", "OK, SSID: " + ssid + ", Pass: " + pass);
            
            delay(2000);
            ESP.restart();
        });
        m_http.onNotFound([this] {
            if (captivePortal()) 
                return;

            m_http.send(404, "text/plain", "404 Not Found");
        });
        m_http.begin();

        // Todo: timeout
        while (true) {
            m_dns.processNextRequest();
            m_http.handleClient();
            //yield();
        }

        return WiFi.status() == WL_CONNECTED;
    }
    
    inline const char * const getApiUsername() const { return m_apiCredentials.Username; }
    inline const char * const getApiPassword() const { return m_apiCredentials.Password; }

private:
    ESP8266WebServer m_http{80};
    DNSServer m_dns;
    APICredentials m_apiCredentials;

    bool captivePortal() {
        if (!isIp(m_http.hostHeader()) ) {
            m_http.sendHeader("Location", String("http://") + m_http.client().localIP().toString(), true);
            m_http.send(302, "text/plain", "");
            m_http.client().stop();
            return true;
        }
        return false;
    }

    int signalStrength(int RSSI) {
        return std::max(0, std::min(2 * (RSSI + 100), 100));
    }
    bool isIp(String str) {
        for (int i = 0; i < str.length(); i++) {
            int c = str.charAt(i);
            if (c != '.' && (c < '0' || c > '9')) {
                return false;
            }
        }
        return true;
    }
};

#endif
