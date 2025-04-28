#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include "html.h"

// WiFi Credentials
const char* ssid = "jdi_na_http://tajna.ufo/";
const char* password = "12345678";

// DNS and Webserver
const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer server(80);

// Custom Hostname
const char* mysecrytwbsite = "tajna.ufo";

// Correct password
const String correctPassword = "heslo";

// pocet zadaných hesel
int pokusynaheslo = 0;


// Welcome page handler
void handleWelcome() {
    // Send the welcome page HTML (password input form)
    server.send(200, "text/html", welcomePage);
}

void handlePasswordCheck() {
    String inputPassword = server.arg("password");

    if (inputPassword == correctPassword) {
        pinMode(18, OUTPUT);
        digitalWrite(18, HIGH);

        server.sendHeader("Location", "/successinobambinobombardino");
        server.send(302, "text/plain", "");
    } else {
        Serial.println("co zadal:");
        Serial.println(inputPassword);

        pokusynaheslo++;

        server.sendHeader("Location", "/wrong");
        server.send(302, "text/plain", "");
    }
}



// Handle unknown paths (404)
void handleOther() {
    server.send(404, "text/plain", "Not found. Try http://tajna.ufo/");
}

// LED blink task for GPIO2
void ledBlinkTask(void *pvParameters) {
    pinMode(2, OUTPUT);
    
    while (true) {
        digitalWrite(2, HIGH);
        vTaskDelay(500 / portTICK_PERIOD_MS);  // Wait for 500ms
        
        digitalWrite(2, LOW);
        vTaskDelay(500 / portTICK_PERIOD_MS);  // Wait for 500ms
    }
}

// Setup function
void setupCode() {
    Serial.begin(115200);

    WiFi.softAP(ssid, password);
    delay(100);
    Serial.println("Access Point started");
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());

    // Start DNS server: redirect tajna.ufo to ESP IP
    dnsServer.start(DNS_PORT, mysecrytwbsite, WiFi.softAPIP());

    // Handle welcome page
    server.on("/", handleWelcome);
	server.on("/successinobambinobombardino", HTTP_GET, []() {
    server.send(200, "text/html", successPage);
	});

	server.on("/wrong", HTTP_GET, []() {
    server.send(200, "text/html", wrongPage);
	});
    // Handle password check form
    server.on("/check-password", HTTP_POST, handlePasswordCheck);
    // Handle 404 page
    server.onNotFound(handleOther);

    server.begin();
    Serial.println("Web server started");
}

// FreeRTOS Task to replace loop
void webTask(void *pvParameters) {
    while (true) {
        dnsServer.processNextRequest();
        server.handleClient();
        vTaskDelay(10 / portTICK_PERIOD_MS);  // Small delay
    }
}

// Main function (ESP-IDF entry point)
extern "C" void app_main() {
    // Initialize Arduino
    initArduino();

    // Setup code
    setupCode();

    // Create FreeRTOS task for web handling
    xTaskCreatePinnedToCore(
        webTask,           // Task function
        "WebTask",         // Task name
        4096,              // Stack size
        NULL,              // Task input
        1,                 // Priority
        NULL,              // Task handle
        APP_CPU_NUM       // Pin to Core 1
    );

    // Create FreeRTOS task for LED blink
    xTaskCreatePinnedToCore(
        ledBlinkTask,      // Task function for LED blinking
        "LedBlinkTask",    // Task name
        2048,              // Stack size
        NULL,              // Task input
        1,                 // Priority
        NULL,              // Task handle
        APP_CPU_NUM       // Pin to Core 1 (same core or Core 0)
    );
}
