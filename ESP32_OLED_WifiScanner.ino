#include "WiFi.h"
#include "Wire.h"
#include "SSD1306.h"

SSD1306 display (0x3c, 5, 4);

void setup()
{
    Serial.begin(115200);

    pinMode(LED, OUTPUT);
    
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");

    display.init ();
    display.flipScreenVertically ();
    display.setFont (ArialMT_Plain_10);
    delay(1000);
    display.clear();
    display.setTextAlignment (TEXT_ALIGN_LEFT);
    display.setFont (ArialMT_Plain_10);
}

void loop()
{
    Serial.println("scan start");

    display.drawString(0, 0, "Scanning...");
    display.display();
    
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    display.clear();
    display.drawString(0, 0, "Scanning...");
    display.display();    
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
        display.drawString(0,10,"No networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            display.drawString( 0 , i*8+10  , String(WiFi.SSID(i)));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            display.drawString( 100 , i*8+10  ,String(WiFi.RSSI(i)));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");

    display.display();
    // Wait a bit before scanning again
    delay(5000);
}
