#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

/*
VCC - 3.3V
GND - GND
CSN - 8
CE - 7
SCK - 13 mac dinh SPI
MISO - 12 SPI
MOSI - 11 SPI

*/
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001"; // Mang ki tu dang chuoi co 6 ki tu (danh dia chi cho kenh tren duong truyen)

void setup() {
  Serial.begin(9600);
  
  if(!radio.begin())
  {
    Serial.println("Module khong khoi dong duoc... !");
    while(1)
    {

    }
  }
  //Cai dat phan TX
  radio.openWritingPipe(address);
  // Moi module RF24L01 co 6 duong truyen (tu 0 den 5)
  // Lenh openWritingPipe mac dinh la duong tren 0
  // mo kenh co dia chi la 00001 tren duong truyen 0 
  // kenh nay ghi data len dia chi 00001
  radio.setPALevel(RF24_PA_MIN); // cai dat bo khuech dai cong suat o muc MAX, HiGH, LOW, MIN (0, -6, -12, -18 dBm)
  radio.setChannel(85); // 125 kenh tu 0-124, TX va RX phai cung kenh
                        // 2.4GHz ~ 2400MHz, buoc kenh la 1MHz
                        // setChannel(80) => 2480MHz
                        // Cao nhat la 2525MHz, tuc la 2.525GHz
  radio.setDataRate(RF24_250KBPS); //Toc do truyen du lieu trong khong khi 
                                   // 250Kbps, 1Mbps, 2Mbps
                                   // 250 thap nhat nhung truyen xa, 1Mb va 2Mb manh nhung truyen khong xa
                                   // Muon truyen 2Mbps thi phai dung it nhat 2 kenh boi vi buoc kenh la 1Mhz
  radio.stopListening(); // cai dat module la TX
  if(!radio.available())
  {
    Serial.println("Chua ket noi duoc voi RX...!");
    Serial.println("CHO KET NOI ...");
  } 
}
void loop() {
  const char text[] = "Hello World"; // tao mang chua chuoi ki tu
  radio.write(&text, sizeof(text)); //Gui du lieu co trong mang text
  // &: tra lai dia chi cua mot bien
  // sizeof(): tra ve so byte bo nho cua mot bien(tra ve tong so byte bo nho cua mot mang)
  Serial.println("Da gui!"); 
  delay(1000);
}




/*
Cai dat cho RX
#include <SPI.h>
#include <RF24-master/nRF24L01.h>
#include <RF24-master/RF24.h>

VCC - 3.3V
GND - GND
CSN - 8
CE - 7
SCK - 13 mac dinh SPI
MOSI - 11 SPI
MISO - 12 SPI

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001"; // Mang ki tu dang chuoi co 6 ki tu (danh dia chi cho kenh tren duong truyen)

void setup() {
  Serial.begin(9600);
  
  if(!radio.begin())
  {
    Serial.println("Module khong khoi dong duoc... !");
    while(1)
    {

    }
  }
 radio.openReadingPipe(1, address);
  // Moi module RF24L01 co 6 duong truyen (tu 0 den 5)
  // Duong truyen 0 da dung cho viec ghi(mac dinh)
  // Vi vay chi dung 1-5, neu dung 0 se bi chong lan
  // mo kenh co dia chi la 00001 tren duong truyen 1 
  // kenh nay chi doc data tren dia chi 00001
  radio.setPALevel(RF24_PA_MIN); // cai dat bo khuech dai cong suat o muc MAX, HiGH, LOW, MIN (0, -6, -12, -18 dBm)
  radio.setChannel(80); // 125 kenh tu 0-124, TX va RX phai cung kenh
                        // 2.4GHz ~ 2400MHz, buoc kenh la 1MHz
                        // setChannel(80) => 2480MHz
                        // Cao nhat la 2525MHz, tuc la 2.525GHz
  radio.setDataRate(RF24_250KBPS); //Toc do truyen du lieu trong khong khi 
                                   // 250Kbps, 1Mbps, 2Mbps
                                   // 250 thap nhat nhung truyen xa, 1Mb va 2Mb manh nhung truyen khong xa
  radio.startListening(); // cai dat module la RX
  if(!radio.available())
  {
    Serial.println("Chua ket noi duoc voi TX...!");
    Serial.println("CHO KET NOI ...");
  } 
}

void loop() {
  if(radio.available())
  {
    char text[32] = ""; 
    radio.read(&text,sizeof(text)); // Doc du lieu thu duoc
    Serial.println(text); // chuyen du lieu len cong Serial
  }
}
*/  
