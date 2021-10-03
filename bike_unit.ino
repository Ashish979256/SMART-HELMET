/* we want to connect rf receiver 
 *                       buzzer gio 4 means d2
 *                       led for power on gpio 5 d1
 *                       velocity measure gpio 0 d3
 *                       rf receiver at 12 pin
 *                       seven segment 5 ppin are gpio1,3,15,
 *                       motor 13,14
 *                       
 *  */
#include <ESP8266WiFi.h>

/*Put your SSID & Password*/
const char* ssid = "redmi";    // Enter SSID here
const char* password = "00000000";  //Enter Password here

const char* server = "api.thingspeak.com";

/* Set GET link with channel ID */
const char* _getLink1 = "https://api.thingspeak.com/apps/thinghttp/send_request?api_key=LGT2IWK6I3Y92VZU";
const char* _getLink2 = "https://https://api.thingspeak.com/apps/thinghttp/send_request?api_key=K74BONN0L8GJZWSD";

WiFiClient client;

 

 int receiver;
 int count=0;
int i=0,val;
float speed=0;
 
 void setup() {
pinMode(1,OUTPUT);//seven segment
   pinMode(3,OUTPUT);//seven
   pinMode(15,OUTPUT);//seven
   pinMode(13,OUTPUT);//relay
   pinMode(12,INPUT);//rf receiver
   pinMode(14,OUTPUT);//relay
   pinMode(0,OUTPUT);//buzzer
   pinMode(5,OUTPUT);//led
  pinMode(4,INPUT);//velocity measure
  



  
  Serial.begin(115200);
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
  
  Serial.println("");
  Serial.println("WiFi connected");


  
  
  
  

}

void loop() {
  receiver=analogRead(A0);
  if(receiver>500)
  {
    digitalWrite(14,HIGH);
    digitalWrite(5,HIGH);
}


//speed measuring
val=digitalRead(4);
  Serial.print(val);
  Serial.print("'");
  while(val==1)
  {
    Serial.print("'");
    delay(100);
    val=digitalRead(4);
    delay(100);
    
  }


 if (val==0)
  
  {
    Serial.print("0");
    digitalWrite(2, LOW);
    
    val=digitalRead(4);
    if(val==1)
    {
      //Serial.print("entered");
    while(val==1)
    {
      Serial.print(".");
      count=count+1;
      val=digitalRead(4);
      delay(100);
    }
    
    }
  }
   
  
 Serial.print("countis =");
  Serial.print(count);
  delay(3000);

 
  if(count>200)
  {
//seven segment will show value 1 else 7
digitalWrite(1,HIGH);
digitalWrite(3,HIGH);


    //calling mobile
     if (client.connect(server,80))     // "184.106.153.149" or api.thingspeak.com
  { 
    String getStr1 = _getLink1;
   /* String getStr2 = _getLink2;

    client.print("GET "+getStr2+"\n");
    client.print("HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n\n\n");
    delay(5000);*/

    client.print("GET "+getStr1+"\n");
    client.print("HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n\n\n");
    delay(2000);
    
}
    
    
    }

else
{
  digitalWrite(1,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(15,HIGH);
  
}



    
  }
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
