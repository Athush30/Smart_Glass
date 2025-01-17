#include <Arduino.h>
#include <WiFi.h>               
#include <Firebase_ESP_Client.h>
#include <string.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"
#include <math.h>
#include <ezButton.h>


// Insert your network credentials
#define WIFI_SSID "Thush"
#define WIFI_PASSWORD "thusa123"
// Insert Firebase project API Key
#define API_KEY "AIzaSyAlwyZHvR3p4GYPqTJYz-eWTT09vP0ooZ8"
// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://projectx-ebe0f-default-rtdb.asia-southeast1.firebasedatabase.app" 

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
//since we are doing an anonymous sign in 
bool signupOK = false;                     

#define xPin 0
#define yPin 1
#define zPin 2

//calibrated minimum and maximum Raw Ranges for each axis
int xMax = 0;
int xMin = 4095;


// Take multiple samples to reduce noise
const int samples = 10;
#define TRIG_PIN 5
#define ECHO_PIN 4
#define led 7

float act_height=0;
const char* status;
bool x= true;
float height;
int state ;
ezButton toggleSwitch(6);


const char * XMin(){
  toggleSwitch.loop();
  
  while (true){
    toggleSwitch.loop();
    state = toggleSwitch.getState();
    if (state == HIGH){
      float x=analogRead(xPin);
      for (int i=0;i<20;i++){
        if(analogRead(xPin)<xMin)
        {
          xMin=analogRead(xPin);
        }
        digitalWrite(led,HIGH);
        delay(500);
        XMax();
        Serial.println("XMAX");
        return "success";
      }
    }
    else{
      Serial.println("else");
      delay(500);
      continue;
    }
  }
}

const char * XMax(){
    toggleSwitch.loop();
    while (true){
      toggleSwitch.loop();
      state = toggleSwitch.getState();
      if (state == LOW){
        float x=analogRead(xPin);
        for (int i=0;i<20;i++){
          if(analogRead(xPin)>xMax)
          {
            xMax=analogRead(xPin);
          }
      
        }
      }
      else{
        delay(500);
        continue;
      }
      digitalWrite(led,LOW);
      delay(500);
      Serial.print("xMin");
      Serial.print(xMin);
      Serial.println("xMax");
      Serial.println(xMax);
      connect();
      Serial.println("XMIN");
      return "success";
      }
}
    


const char *connect(){
  toggleSwitch.loop();
  int state = toggleSwitch.getState();
  if (state == HIGH){
    for (int i=0;i<20;i++){
      act_height+=distance()*sin(angle());
    }
    act_height/=20;
    Serial.println(act_height);
    Serial.println("CONNECT");
    
  }
  else{
    delay(500);
    
    connect();
  }
  return "success";
}
    

    
    

float angle(){
        int xRaw=0,yRaw=0,zRaw=0;

        for(int i=0;i<samples;i++)
        {
          xRaw+=analogRead(xPin);
          yRaw+=analogRead(yPin);
          zRaw+=analogRead(zPin);
        }

        xRaw/=samples;
        yRaw/=samples;
        zRaw/=samples;

        long xMilliG = map(xRaw, xMin, xMax, -1000, 1000);
        float x_g_value = xMilliG / 100.0;
        float angle = 180-((acos(x_g_value/10))*180.0/M_PI);
        

        delay(200);
        return angle;
}

float distance(){
        digitalWrite(TRIG_PIN, LOW);
        delayMicroseconds(15);
        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG_PIN, LOW);

        long duration = pulseIn(ECHO_PIN, HIGH);
        float distance = duration * 0.034 / 2;

        delay(500);
        return distance;
}




void setup() {
        Serial.begin(115200);
        pinMode(TRIG_PIN, OUTPUT);
        pinMode(ECHO_PIN, INPUT);
        pinMode(led,OUTPUT);
        toggleSwitch.setDebounceTime(50);

        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        Serial.print("Connecting to Wi-Fi");
        while (WiFi.status() != WL_CONNECTED){
          Serial.print(".");
          delay(300);
        }
        Serial.println();
        Serial.print("Connected with IP: ");
        Serial.println(WiFi.localIP());
        Serial.println();

        
        config.api_key = API_KEY;
        config.database_url = DATABASE_URL;

        if (Firebase.signUp(&config, &auth, "", "")){
          Serial.println("ok");
          signupOK = true;
        }
        else{
          Serial.printf("%s\n", config.signer.signupError.message.c_str());
        }

        
        config.token_status_callback = tokenStatusCallback; 
        Firebase.begin(&config, &auth);
        Firebase.reconnectWiFi(true);

}

void loop() {
       
        if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
          sendDataPrevMillis = millis();
          if (x==true){
            XMin();
            x=false;
            Serial.println("act_height");
          }
          Serial.println("act_height");
          Serial.println(act_height);
          if (Firebase.RTDB.setFloat(&fbdo, "act_height", act_height)){
            Serial.println("PASSED");
            Serial.println("PATH: " + fbdo.dataPath());
            Serial.println("TYPE: " + fbdo.dataType());
          }
          else {
            Serial.println("FAILED");
            Serial.println("REASON: " + fbdo.errorReason());
          }
          
          if (Firebase.RTDB.setString(&fbdo, "connection status", "success")){
            Serial.println("PASSED");
            Serial.println("PATH: " + fbdo.dataPath());
            Serial.println("TYPE: " + fbdo.dataType());
          }
          else {
            Serial.println("FAILED");
            Serial.println("REASON: " + fbdo.errorReason());
          }
    
          
          for (int i=0;i<10;i++){
            height += distance() * sin(angle());
          }
          height/=20;
          if (height>act_height){
            Serial.println("g");
            status = "down";
            if (Firebase.RTDB.setString(&fbdo, "status", status)){
              Serial.println("PASSED");
            }
            else {
              Serial.println("FAILED");
              Serial.println("REASON: " + fbdo.errorReason());
            }
          }
          if (height<act_height){
            status="up";
            if (Firebase.RTDB.setString(&fbdo, "status", status)){
              Serial.println("PASSED");
            }
            else {
              Serial.println("FAILED");
              Serial.println("REASON: " + fbdo.errorReason());
            }
          }
          Serial.print(height);
          Serial.print(act_height);
          Serial.println(status);
          
        }
        delay(100);

}

