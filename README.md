📡 Secret Scout Messages — WiFi Access Point
This project creates a hidden WiFi network where users must enter a secret password to "unlock" mysterious scout stories.

Built using:

📶 ESP32 (or ESP8266)

📜 Arduino framework + FreeRTOS tasks

🌐 Captive DNS + Web Server

💡 LED control when the password is correct

✨ Features
Creates a WiFi hotspot (SSID: jdi_na_tajna.ufo, password 12345678).

Custom "secret website" at http://tajna.ufo.

Shows a beautiful welcome page with scout conspiracy theories.

Asks for a password.

If password is correct:

Redirects to a success page.

Turns ON an LED on GPIO 18.

If password is wrong:

Redirects to a wrong page.

Increases failed attempt counter (pokusynaheslo).

LED on GPIO 2 blinks continuously to show the server is alive.

📜 How it works
ESP32 boots up, sets up a WiFi Access Point.

DNS Server redirects all requests to tajna.ufo.

Web Server serves a welcome page and password check form.

When a password is submitted:

Correct password → redirect to success page and activate LED.

Wrong password → redirect to wrong page.

Two FreeRTOS tasks run:

Web server handling

Blinking an LED for heartbeat signal.

🛠 Installation
Install Arduino IDE (with ESP32 Board Manager).

Clone or download this project.

Install required libraries:

WiFi.h
WebServer.h
DNSServer.h

Flash the code to your ESP32.

Connect your device to the WiFi network:

SSID: jdi_na_tajna.ufo

Password: 12345678

Open a browser and navigate to http://tajna.ufo.

🧩 Project Structure

File	Purpose
main.cpp	Main server and logic code
html.h	Contains HTML for welcome, success, and wrong pages
README.md	Project documentation
⚡ Hardware Requirements
ESP32 Dev Module (or compatible)

LED + 220Ω resistor connected to GPIO 18 (optional but recommended)

📖 Password Behavior
Correct password is heslo.

After correct password:

LED on pin 18 turns ON permanently.

Wrong password:

Printed to Serial Monitor.

Redirects to "Wrong Password" page.

📋 License
MIT License.
Free to use, modify and share.
Just don't use it for evil spy stuff 😉.

🛡 Happy Hacking!