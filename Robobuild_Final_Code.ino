#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

//SSID and Password of ESP Access Point
const char* ssid = "Robo Build";
const char* password = "012345678";

#define ENA   0     // D3
#define IN_1  5     // D1
#define IN_2  4     // D2
#define IN_3  14    // D5
#define IN_4  12    // D6
#define ENB   13    // D7
#define FLight 16   // D0
#define RRLight 2  // D4
#define RLLight 15  // D8


String command;  // Command from app
int botspeed = 150;

ESP8266WebServer server(80);

void setup() {
 
  Serial.begin(115200);

 pinMode(ENA, OUTPUT);
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT);
 pinMode(ENB, OUTPUT);
 pinMode(FLight, OUTPUT);
 pinMode(RRLight, OUTPUT);
 pinMode(RLLight, OUTPUT);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void loop() {
    server.handleClient();
    
      command = server.arg("State");
           if (command == "F") Forward();
      else if (command == "B") Backward();
      else if (command == "R") FRight();
      else if (command == "L") FLeft();
      else if (command == "D") BRight();
      else if (command == "E") BLeft();
      else if (command == "O") lighton();
      else if (command == "P") lightoff();
      else if (command == "1") botspeed = 80;
      else if (command == "2") botspeed = 120;
      else if (command == "3") botspeed = 160;
      else if (command == "4") botspeed = 200;
      else if (command == "5") botspeed = 255;
      else if (command == "S") botstop();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}

void Forward(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, botspeed);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, botspeed);
  }

void Backward(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, botspeed);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, botspeed);
      
      digitalWrite(RRLight, HIGH);
      digitalWrite(RLLight, HIGH);
      
  }

void FRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, botspeed);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, botspeed);
  }

void FLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, botspeed);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, botspeed);
  }

void BRight(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, botspeed);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, botspeed);

      digitalWrite(RRLight, HIGH);
}

void BLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, botspeed);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, botspeed);

      digitalWrite(RLLight, HIGH);
}

void botstop(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, botspeed);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, botspeed);

      digitalWrite(RRLight, LOW);
      digitalWrite(RLLight, LOW);
 }

 void lighton(){
  digitalWrite(FLight, HIGH);
 }

 void lightoff(){
  digitalWrite(FLight, LOW);
 }
