#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>   
 #define DHTPIN D2  
 #define DHTTYPE DHT11  
 DHT dht(DHTPIN, DHTTYPE);
uint8_t h, t;
int fire;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "vukGsVAZT0QPOR7fQjvQ80Q1HgipynSb";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IOT";
char pass[] = "12345678";
        // What digital pin we're connected to




// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  h = dht.readHumidity();
  t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Serial.println(h);
  Serial.println(t);
  
  
  
}

void setup()
{
  // Debug console
  Serial.begin(115200);
dht.begin();
delay(10);
  Blynk.begin(auth, ssid, pass);
  pinMode(D7,OUTPUT);
  pinMode(D5,INPUT);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  

  // Setup a function to be called every second
  //timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  fire=digitalRead(D5);
  if(fire==0)
  {
    digitalWrite(D7,HIGH);
    Serial.println("FIRE DETECTED");
    Blynk.virtualWrite(V2,"FIRE DETECTED! \n" );
    Blynk.notify("FIRE DETECTED");
    Blynk.email("surajkumarpattanaik3@gmail.com","FIRE ALERT","FIRE DETECTED");
  }
  else
  {
    digitalWrite(D7,LOW);
    Serial.println("YOUR HOME IS SAFE ");
    Blynk.virtualWrite(V2,"YOUR HOME IS SAFE! \n");
  }
  delay(1000);
 //timer.run();
  sendSensor();
}
