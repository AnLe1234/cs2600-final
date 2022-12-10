#include <PubSubClient.h>
#include <WiFi.h>
#include <Keypad.h>
#include "secret.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char *ssid = SECRET_SSID;        // your network SSID (name)
char *pass = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
// define the symbols on the buttons of the keypad
char keys[4][4] = {
{'1', '2', '3'},
{'4', '5', '6'},
{'7', '8', '9'}
};
byte rowPins[4] = {14, 27, 26}; // connect to the row pinouts of the keypad
byte colPins[4] = {13, 21, 22}; // connect to the column pinouts of the keypad
// initialize an instance of class NewKeypad
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

WiFiClient wifiClient;
PubSubClient client;
// MqttClient mqttClient(wifiClient);
IPAddress mqtt_server(IP_ADDRESS);

// const char broker[] = "test.mosquitto.org";
int        port     = 1883;
const char topic[]  = "keypad";

//set interval for sending messages (milliseconds)
const long interval = 500;
unsigned long previousMillis = 0;

int count = 0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(500);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(mqtt_server);
  client.setClient(wifiClient);
  client.setServer(mqtt_server, port);
  // if (!mqttClient.connect(mqtt_server, port)) {
  //   Serial.print("MQTT connection failed! Error code = ");
  //   Serial.println(mqttClient.connectError());

  //   while (1);
  // }
  connect();
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  // client.poll();

  // unsigned long currentMillis = millis();

  // if (currentMillis - previousMillis >= interval) {
  //   // save the last time a message was sent
  //   previousMillis = currentMillis;

  //   char keyPressed = myKeypad.getKey();
  //   // char *temp_char = String(keyPressed);
  //   if (keyPressed) {
  //     String temp_str = String(keyPressed);
  //     char k[2];
  //     temp_str.toCharArray(k, 2);

  //     Serial.print("Sending message to topic: ");
  //     Serial.println(topic);
  //     Serial.printf("Key Pressed: %s\n", k);
  //     // publish key pressed
  //     client.publish(topic, k);
  //   }
  // }

  if (!client.connected()) {
    connect();
  }

  // client.setKeepAlive(5);
  char keyPressed = myKeypad.getKey();

  if (keyPressed) {
    String temp_str = String(keyPressed);
    char k[2];
    temp_str.toCharArray(k, 2);

    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.printf("Key Pressed: %s\n", k);
    // publish key pressed
    client.publish(topic, k);
  }
}

void connect() {
    if (!client.connect("ESP-Client", USER, PASSWORD)) {
    Serial.print("Fail to connect! Error = ");
    Serial.println(client.state());
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}