#include <SPI.h>
#include <LoRa.h>
#include <dht.h>
dht DHT;
#define DHT11_PIN A1
int counter = 0;
uint8_t datasend[72];
float temperature,humidity,tem,hum;
char tem_1[8]={"\0"},hum_1[8]={"\0"};

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(8681E5)) {

    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
void dhtTem()
{
        temperature = DHT.read11(DHT11_PIN);    //Read Tmperature data
        tem = DHT.temperature*1.0;      
        humidity = DHT.read11(DHT11_PIN);      //Read humidity data
        hum = DHT.humidity* 1.0;             
       
        Serial.println(F("The temperature and humidity:"));
        Serial.print("[");
        Serial.print(tem);
        Serial.print("℃");
        Serial.print(",");
        Serial.print(hum);
        Serial.print("%");
        Serial.print("]");
        Serial.println("");
        
        delay(2000);
}

void dhtWrite()
{
      char data[50] = "\0";

      dtostrf(tem,0,1,tem_1);
      dtostrf(hum,0,1,hum_1);

      strcat(data,"The temperature and humidity:");
      strcat(data,"[");
      strcat(data,tem_1);
      strcat(data,"C");
      strcat(data,",");
      strcat(data,hum_1);
      strcat(data,"%");
      strcat(data,"]");
      strcpy((char *)datasend,data);
}
void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);
  dhtTem();
  dhtWrite();
  // send packet
  LoRa.beginPacket();
  LoRa.print((char*)datasend);
  //LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}

