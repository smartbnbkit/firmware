#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

#include "Resources.h"

class Configuration {
public:
    Configuration() { }
    bool begin(const char *ssid, const char *pass = NULL) {
        WiFi.mode(WIFI_AP_STA);

        if (pass) WiFi.softAP(ssid, pass);
        else      WiFi.softAP(ssid);

        delay(500);

        m_dns.setErrorReplyCode(DNSReplyCode::NoError);
        m_dns.start(53, "*", WiFi.softAPIP());

        m_http.on("/", [this] {
            String page = FPSTR(Resource_Index);
            page.replace("%ssid%", WiFi.SSID());
            page.replace("%pass%", WiFi.psk());
            
            // Todo: make this an ajax call with preloader
            int n = WiFi.scanNetworks();
            if (n == 0) {
                page.replace("%scan_results%", "<tr><td>No networks found. Refresh to scan again.</td></tr>");
            } else {
                String results;
                for (int i = 0; i < n; i++) {
                    auto ssid = WiFi.SSID(i);
                    auto rssi = WiFi.RSSI(i);

                    String item = FPSTR(Resource_NetworkRow);
                    item.replace("%ssid%", ssid);
                    item.replace("%strength%", String(signalStrength(rssi)));
                    item.replace("%fa-wifi%", FPSTR(Resource_WiFiIcon));
                    
                    if (WiFi.encryptionType(i) != ENC_TYPE_NONE) {
                        item.replace("%fa-lock%", FPSTR(Resource_LockIcon));
                    } else {
                        item.replace("%fa-lock%", "");
                    }
                    results += item;
                }
                page.replace("%scan_results%", results);
            }

            m_http.send(200, "text/html", page);
        });
        m_http.on("/save", [this] {
            String ssid = m_http.arg("ssid").c_str();
            String pass = m_http.arg("password").c_str();
            
            // Save to flash
            WiFi.begin(ssid.c_str(), pass.c_str());

            m_http.send(200, "text/plain", "OK, SSID: " + ssid + ", Pass: " + pass);
            
            delay(2000);
            ESP.reset();
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

private:
    ESP8266WebServer m_http{80};
    DNSServer m_dns;

    bool captivePortal() {
        if (!isIp(m_http.hostHeader()) ) {
            m_http.sendHeader("Location", String("http://") + ipToString(m_http.client().localIP()), true);
            m_http.send(302, "text/plain", "");
            m_http.client().stop();
            return true;
        }
        return false;
    }

    int signalStrength(int RSSI) {
        int quality = 0;

        if (RSSI <= -100) {
            quality = 0;
        } else if (RSSI >= -50) {
            quality = 100;
        } else {
            quality = 2 * (RSSI + 100);
        }
        return quality;
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
    String ipToString(IPAddress ip) {
        String res = "";
        for (int i = 0; i < 3; i++) {
            res += String((ip >> (8 * i)) & 0xFF) + ".";
        }
        res += String(((ip >> 8 * 3)) & 0xFF);
        return res;
    }
};
