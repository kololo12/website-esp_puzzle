#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include "html.h"
#include <vector>

//admin state
bool adminUnlocked = false;
const int adminled = 19;

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

//list uspěšných hráčů
std::vector<String> successfulPlayers;


// Welcome page handler
void handleWelcome() {
    // Send the welcome page HTML (password input form)
    server.send(200, "text/html", welcomePage);
}

// Funkce pro převod písmen na malá a odstranění háčků/čárek
String normalizeString(String input) {
  input.toLowerCase();  // Převede na malá písmena
  input.replace("á", "a");
  input.replace("é", "e");
  input.replace("í", "i");
  input.replace("ó", "o");
  input.replace("ú", "u");
  input.replace("ý", "y");
  input.replace("č", "c");
  input.replace("ď", "d");
  input.replace("ě", "e");
  input.replace("ň", "n");
  input.replace("ř", "r");
  input.replace("š", "s");
  input.replace("ť", "t");
  input.replace("ů", "u");
  input.replace("ž", "z");
  return input;
}

void handlePasswordCheck() {
    // Získání jednotlivých částí hesla z formuláře
    String part1 = server.arg("part1");
    String part2 = server.arg("part2");
    String part3 = server.arg("part3");

	part1 = normalizeString(part1);
	part2 = normalizeString(part2);
	part3 = normalizeString(part3);
    // Spojení částí do jednoho celku
    String inputPassword = part1 + part2 + part3;

    // Debug: výpis zadaného hesla
    Serial.println("-------------------------------------");
	Serial.print("Zadáno heslo: ");
    Serial.println(inputPassword);
	Serial.println("-------------------------------------");

    // Porovnání se správným heslem
    String correctPassword = "propastnetopyrzatoichi";  // nastav si správné heslo zde

    if (inputPassword == correctPassword) {
        pinMode(18, OUTPUT);
        digitalWrite(18, HIGH);

        server.sendHeader("Location", "/successinobambinobombardino");
        server.send(302, "text/plain", "");
		
		String nickname = server.arg("nickname");

		if (nickname.length() > 0) {
			successfulPlayers.push_back(nickname);
			Serial.println("-------------------------------------");
			Serial.print("uhádlhráč: ");
			Serial.println(nickname);
			Serial.println("-------------------------------------");
		}

    } else {
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

void buttonCheckTask(void *pvParameters) {
    const int buttonPin = 14;
    pinMode(buttonPin, INPUT_PULLUP);
	pinMode(adminled, OUTPUT);
    bool lastState = HIGH;

    while (true) {
        bool currentState = digitalRead(buttonPin);

        if (lastState == HIGH && currentState == LOW) {
            adminUnlocked = true;
			digitalWrite(adminled, HIGH);
			Serial.println("-------------------------------------");
			Serial.println("ADMIN stránka odemčena tlačítkem!");
			Serial.println("Hráči kteří dokončili hru:");

            if (successfulPlayers.empty()) {
                Serial.println("Zatím nikdo nedokončil hru.");
				Serial.println("-------------------------------------");
            } else {
                for (size_t i = 0; i < successfulPlayers.size(); i++) {
                    Serial.printf("%d. %s\n", i + 1, successfulPlayers[i].c_str());
                }
				Serial.println("-------------------------------------");
            }

            vTaskDelay(1000 / portTICK_PERIOD_MS);  // debounce + ochrana proti opakování
        }

        lastState = currentState;
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

// Setup function
void setupCode() {
    Serial.begin(115200);

    WiFi.softAP(ssid, password);
	WiFi.setTxPower(WIFI_POWER_19_5dBm);
    delay(100);
	Serial.println("-------------------------------------");
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
	
	server.on("/admin", HTTP_GET, []() {
    if (adminUnlocked) {
        String page = adminPageHeader;

        if (successfulPlayers.empty()) {
            page += "<li><em>Žádní hráči zatím nedokončili hru.</em></li>";
        } else {
            for (size_t i = 0; i < successfulPlayers.size(); i++) {
                page += "<li>" + String(i + 1) + ". " + successfulPlayers[i] + "</li>";
            }
        }

        page += adminPageFooter;
        server.send(200, "text/html", page);
		} else {
        server.send(403, "text/html", accessDeniedPage);
		}
	});
	
	server.on("/logout", HTTP_POST, []() {
		adminUnlocked = false;
		digitalWrite(adminled, LOW);
		server.sendHeader("Location", "/");
		server.send(302, "text/plain", "");
	});

    server.begin();
    Serial.println("Web server started");
	Serial.println("-------------------------------------");
}

// FreeRTOS Task to replace loop
void webTask(void *pvParameters) {
    while (true) {
        dnsServer.processNextRequest();
        server.handleClient();
        vTaskDelay(10 / portTICK_PERIOD_MS);  
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
	
	// Create FreeRTOS task for button check
	xTaskCreatePinnedToCore(
		buttonCheckTask,
		"ButtonCheckTask",
		2048,
		NULL,
		1,
		NULL,
		APP_CPU_NUM
	);

}
