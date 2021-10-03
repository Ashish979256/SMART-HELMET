//irsensor1   13

//gps         5,4
//rf transmitter 0
//led for      5
//vibration  16    
//mq3       12

#include <ESP8266WiFi.h>
//#include <SPI.h>
//#include <WiFi.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

//ggps declaration
TinyGPSPlus gps;  //The TinyGPS++ object



SoftwareSerial ss(4, 5);// The serial connection to the GPS device

float latitude , longitude;



String  lat_str , lng_str;







/*Put your SSID & Password*/
const char* ssid = "redmi";    //Enter SSID here
const char* password = "00000000";  //Enter Password here

const char* server2 = "api.thingspeak.com";

/* Set GET link with channel ID */
const char* _getLink1 = "https://api.thingspeak.com/update?api_key=K83IRKRKIX64EYTH&field1=";
const char* _getLink2 = "https://api.thingspeak.com/update?api_key=K83IRKRKIX64EYTH&field2=";

WiFiClient client;

//declaration of various input and output

int ir1=15,vib=16,tx=0,mq3=12,led=13;
int ir1val=0,ir2val=0,vibval=0,mq3val=0;
void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(ir1,INPUT);
  pinMode(2,OUTPUT);
  pinMode(mq3,INPUT);
  pinMode(vib,INPUT);
  pinMode(led,OUTPUT);
 
  pinMode(tx,OUTPUT);
  digitalWrite(led,LOW);
  digitalWrite(2,LOW);
  digitalWrite(tx,LOW);
  

  // check alcohol and helmet waring detection
  ir1val=digitalRead(ir1);
 
  mq3val=digitalRead(mq3);
  vibval=digitalRead(vib);
  //Serial.println(ir2val);
  //Serial.println(mq3val);
  Serial.println("trying to detect alcohol and wearing of helmet");
  Serial.print("alcohol val");
  Serial.print(mq3val);
  ir1val=1;
  while(ir1val==0)
  {
    
    Serial.print(".");
    ir1val=digitalRead(ir1);
    delay(1000);
    
  }
  Serial.print("helmet wearing detected");
  //Serial.println(ir1val);
  if(ir1val==1)
  {
    
      if(mq3val==1)
      {
        Serial.println("no alcohol detected");
        digitalWrite(tx,HIGH);
        digitalWrite(led,HIGH);
         digitalWrite(16,HIGH);
         digitalWrite(2,HIGH);
        Serial.println("you are not drunk and have wear helmet");
        Serial.println("transmitter on");
      }
 }
    


//now connecting to wifi

  
     ss.begin(9600);//for gps serial connection
  delay(1000);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.print("");
  Serial.print("WiFi connected");

  


  // Print the IP address

  //Serial.print(WiFi.localIP());



  
  
}

void loop() 
{

 vibval=digitalRead(vib);
  Serial.print(vibval);
  while(vibval==1)
  {
    
    if (ss.available() > 0)
{
    if (gps.encode(ss.read()))

    {

      if (gps.location.isValid())

      {

        latitude = gps.location.lat();

        lat_str = String(latitude , 6);
        Serial.println("latitude");
        Serial.println(lat_str);

        longitude = gps.location.lng();

        lng_str = String(longitude , 6);
        Serial.println("longitude");
        Serial.println(lng_str);
        delay(5000);

      }
    }
   }  
  
 vibval=digitalRead(vib);

  }
    
  Serial.println("accident occured");
 

 if (client.connect(server2,80))     // "184.106.153.149" or api.thingspeak.com
  { 
    String getStr1 = _getLink1;
     String getStr2 = getStr1+lat_str+"&field2="+lng_str+"&field3=0";//
   
     
  

    client.print("GET "+getStr2+"\n");
    client.print("HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n\n\n");
    delay(2000);
    
     while(client.available()){
  char c = client.read();
  Serial.print(c);
    }
    Serial.println("");
  
  }
  client.stop();
    
    
    
Serial.println("field1 updated");
delay(6000);








 }
     

 
 
  
