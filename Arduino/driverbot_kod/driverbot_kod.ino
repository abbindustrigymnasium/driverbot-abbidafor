//includes outside libraries
#include "EspMQTTClient.h"
//Install libraries PubSubClient and EspMQTTClient
#include <Servo.h>

Servo servo;

//funktion som körs när det är uppkopplat på mqtt tjänsten
void onConnectionEstablished();

//konfigurationsparametrar som används
EspMQTTClient client(
  "TN_24GHz_F3EDB7",           // Wifi ssid
  "xxxxxxxxxxxx",           // Wifi password
  "maqiatto.com",  // MQTT broker ip
  1883,             // MQTT broker port
  "ida.forsman@abbindustrigymnasium.se",            // MQTT username
  "xxxxxxxxxxxx",       // MQTT password
  "driverbot",          // Client name
  onConnectionEstablished, // Connection established callback
  true,             // Enable web updater
  true              // Enable debug messages
);

// definerar variabler
#define motorPinRightDir  0//D2
#define motorPinRightSpeed 5//D1

#define motorPinLeftDir 2
#define motorPinLeftSpeed 4

void setup() {
  //konfigurarar om det är en output eller input
  servo.attach(14); //D5
  pinMode(motorPinRightDir, OUTPUT);
  pinMode(motorPinRightSpeed, OUTPUT);
  pinMode(motorPinLeftDir, OUTPUT);
  pinMode(motorPinLeftSpeed, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  //säger att den ska vara av innan koden körs
  digitalWrite(LED_BUILTIN, LOW);
  //sätter uppladdningshastigheten till 115200
  Serial.begin(115200);
  //värdet på servot är noll
  servo.write(0);

  // väntar 2 s
  delay(2000);
}

//sväng vänster eller höger
// turn 
void turn(bool left, int degrees) {

//om left är true åker den så många grader som man får i meddelandet
  if (left == true)
  {
    degrees -= 90;

    if (degrees < 0)
    {
      degrees = 0;
      
      //digitalwrite när man svänger eftersom det är 1 eller 0
      //analogwrite på hastigheten för att man behöver en annan skala än 1 eller 0
      digitalWrite(motorPinLeftDir, 1);
      analogWrite(motorPinLeftSpeed, 1000);
    }
    servo.write(degrees);
    Serial.println("Åk Vänster!");
  }
  else
  {
 //om left inte är true svänger den höger
    degrees += 90;
    if (degrees > 180)
    {
      degrees = 180;
      digitalWrite(motorPinLeftDir, 1);
      analogWrite(motorPinLeftSpeed, 1000);
    }
    servo.write(degrees);
    Serial.println("Åk Höger!");

  }
  Serial.println(degrees);


}

void drive(bool dir, int speed) {

  //Om du vill åka rakt fram eller bak
  servo.write(90);

  Serial.println("Åk!");

  Serial.println(speed);
  digitalWrite(motorPinLeftDir, dir);
  analogWrite(motorPinLeftSpeed, speed);

  digitalWrite(motorPinRightDir, dir);
  analogWrite(motorPinRightSpeed, speed);

  digitalWrite(LED_BUILTIN, dir);

}

void onConnectionEstablished()
{
  Serial.println("onConnectionEstablished");


//subscriba till topicen
  client.subscribe("ida.forsman@abbindustrigymnasium.se/drive", [] (const String & payload) {
    char info = payload.charAt(0);
    int length = payload.length();
    String value = payload.substring(1, length);
    int speed = value.toInt();
    //om info är f eller b,om den åker fram eller bak
    if (info == 'f' || info == 'b'  )
    {
      //om info är f blir dir true och bilen åker frammåt, om dir är false åker den bakåt
      bool dir = false;
      if (info == 'f')
        dir = true;
      drive(dir, speed);
    }
    else if (info == 'r' || info == 'l'  )
    {
      //om info är l så blir dir true och bilen svänger vänster, om dir är false svänger den höger
      bool dir = false;
      if (info == 'l')
        dir = true;
      turn(dir, speed);
    }
    Serial.println(payload);

  });
//publishar this is a message
  client.publish("ida.forsman@abbindustrigymnasium.se/drive", "This is a message");

}


void loop() {
  // put your main code here, to run repeatedly:
  // client är en klass där man kan göra olika operaritoner mot mqtt servern
  client.loop();
}
