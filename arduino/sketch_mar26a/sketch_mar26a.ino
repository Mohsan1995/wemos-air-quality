#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>
#define PIN D4
#define NUM_LEDS 8
#define SSID "AndroidAP"
#define PASS "cqxj1571"

void colorAdafruit(int R,int G,int B);
void graph(int value);
void connectToWifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

//SSID of your network
char ssid[] = SSID; //SSID of your Wi-Fi router
char pass[] = PASS; //Password of your Wi-Fi router
char msg[50];
char topicPub[] = "sensor/sound";
const char* mqtt_server = "192.168.43.141";

//Sound sensor
int sensorSoundPin = A0;
int sensorValue = 0;

int sensorMovePin = D7;
int val;

int R = 0;
int G = 0;
int B = 255;

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  connectToWifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  strip.begin();
  strip.show();
}


// the loop function runs over and over again forever
void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();
  delay(5000);
  sensorValue = analogRead(sensorSoundPin);
  snprintf (msg, 75, "%ld", sensorValue);
  client.publish(topicPub, msg);

  if(sensorValue > 190){
    R = 255;
    G = 0;
    B = 0;
  } else if ( sensorValue > 150  && sensorValue < 175){
     R = 255;
     G = 165;
     B = 0;
  }else if(sensorValue < 150){
    R = 77;
    G = 225;
    B = 0;
  }

  colorAdafruit(R,G,B);
  clearColorAdafruit();

}

void connectToWifi(){
   delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to...");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected successfully");
}

void graph(int value){

  while(--value){
    Serial.print("*");
  }

  Serial.println("*");

}

void callback(char* topic, byte* payload, unsigned int length) {
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");
 for (int i=0;i<length;i++) {
  char receivedChar = (char)payload[i];
  Serial.print(receivedChar);
  Serial.println();
 }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void colorAdafruit(int R,int G,int B){

  for(int i=0;i<NUM_LEDS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(R,G,B)); // Moderately bright green color.
    strip.show(); // This sends the updated pixel color to the hardware.
    delay(500); // Delay for a period of time (in milliseconds).
  }

}


void clearColorAdafruit(){

  for(int i=0;i<NUM_LEDS;i++){

    strip.setPixelColor(i, strip.Color(0,0,0)); // Moderately bright green color.

    strip.show(); // This sends the updated pixel color to the hardware.

    delay(500); // Delay for a period of time (in milliseconds).

  }

}



