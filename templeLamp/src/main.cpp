#include <Arduino.h>
#include <WiFi.h>
#include <EEPROM.h>

#include "zodiac.h"

/* Defines and Macros */
#define LINE_STR_SIZE	80


/* Global variables */
int signal = 1;
int status;
const char *ssid = "AndroidAP3888";
const char *pwd = "bpep0558";
char recv[LINE_STR_SIZE];
IPAddress server(192,168,43,33);
WiFiClient zodiac;

/* Functions */
void setup() {
	// Begin functions
	Serial.begin(9600);

	// Initialisation
	pinMode (LED_BUILTIN, OUTPUT);
	
	// Connect to wifi
	while (WiFi.status() != WL_CONNECTED) {
		Serial.println("Attempting to connect...");
		WiFi.begin(ssid, pwd);
		delay(500);
	}
	
	digitalWrite(LED_BUILTIN, signal);
	Serial.println("WiFi Connection Established");
	if (status = zodiac.connect(server, 42069)) {
		Serial.println("Connected to server");
	}
}

void loop() {

	if (status) {  
		signal ^= 1;  
		if (zodiac.readBytes(recv, LINE_STR_SIZE)) {
			Serial.println(recv);
		}
		
		digitalWrite(LED_BUILTIN, signal);
		delay(5);
	}

}