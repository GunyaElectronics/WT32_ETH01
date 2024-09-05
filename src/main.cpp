#include <ETH.h>
#include <WiFi.h>

#define ETH_POWER_PIN    16
#define ETH_MDIO_PIN     18
#define ETH_MDC_PIN      23
#define ETH_PHY_ADDR     1

void setup()
{
    Serial.begin(115200);
    delay(1000);

    // Power on LAN8720 PHY
    pinMode(ETH_POWER_PIN, OUTPUT);
    digitalWrite(ETH_POWER_PIN, HIGH);
    delay(500);

    ETH.begin(ETH_PHY_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_PHY_LAN8720);

    Serial.println("Wait link up...");
    while (!ETH.linkUp()) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    ETH.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
    Serial.println("Wait DHCP...");
    while (ETH.localIP() == INADDR_NONE) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.print("IP: ");
    Serial.println(ETH.localIP());

    Serial.print("MAC: ");
    Serial.println(ETH.macAddress());

    Serial.print("Gateway: ");
    Serial.println(ETH.gatewayIP());

    Serial.print("DNS: ");
    Serial.println(ETH.dnsIP());
}

void loop()
{
}
