#include <ESP8266WiFi.h>
#include <PubSubClient.h>

void graph(int value);
void connectToWifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

//SSID of your network
char ssid[] = "AndroidAP"; //SSID of your Wi-Fi router
char pass[] = "cqxj1571"; //Password of your Wi-Fi router
char msg[50];
char topicPub[] = "sensor/sound";
const char* mqtt_server = "192.168.43.141";

WiFiClient espClient;
PubSubClient client(espClient);

//Sound sensor
int sensorSoundPin = A0; 
int sensorValue = 0;

int sensorMovePin = D7;
int val;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  connectToWifi();
  //pinMode(sensorMovePin, INPUT); 
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}


// the loop function runs over and over again forever
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  /*val = digitalRead(sensorMovePin);
  Serial.println(val);
  if (val == LOW){
    Serial.println("NO MOTION");
    client.publish(topicPub, "No motion");
  }else{
    Serial.println("MENTION");
    client.publish(topicPub, "motion");
  }
  delay(100);
  */
  delay(5000);
  sensorValue = analogRead(sensorSoundPin);
  snprintf (msg, 75, "%ld", sensorValue);
  client.publish(topicPub, msg);
  
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




