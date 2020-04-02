#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

/*
 * Typical pin layout used:
 * ----------------------------------------------
 *             MFRC522      Arduino       NodeMCU 
 *             Reader/PCD   Uno/101             
 * Signal      Pin          Pin           Pin        
 * ----------------------------------------------
 * RST/Reset   RST          9             D3        
 * SPI SS      SDA(SS)      10            D4       
 * SPI MOSI    MOSI         11 / ICSP-4   D7       
 * SPI MISO    MISO         12 / ICSP-1   D6      
 * SPI SCK     SCK          13 / ICSP-3   D5        
 */

#define LED_PIN         D0
#define RST_PIN         D3          // Configurable, see typical pin layout above
#define SS_PIN          D4         // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

Adafruit_SSD1306 display = Adafruit_SSD1306();

// WiFi credentials.
// Set password to "" for open networks.
const char* ssid = "---YOUR-WIFI-NETWORK-NAME---";
const char* password = "---YOUR-WIFI-PASSWORD---";
const char* KEY_thinkspeak = "---THINKSPEAK-WRITE-KEY--- ";

void setup()
{
  Serial.begin(9600);// For nodemcu

  // Setting Led Pin Mode
  pinMode(LED_PIN,OUTPUT);

  //Begin: Setup for WIFI 
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) { 
    delay(1000);
    Serial.print("Connecting..\n"); 
  }
  Serial.print("Connected..\n");
  //End : Setup for WIFI

   //Begin: Initialization RFID Reader
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  // End: Initialization RFID Reader
  
  // Begin: Screen Initialization Code 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2, 3);
  display.print("S T G O");
  display.display(); 
  display.setCursor(10, 10);
  display.setTextSize(2); 
  display.print("HACKATHON"); 
  display.display();
  delay(2000);
  
  display.clearDisplay();
   display.setTextSize(1);
  display.setCursor(5,5);
  
  display.print("Show Your Card...");
  display.display();
  // End: Screen Initialization Code 


}
void loop()
{
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
    //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  String name="";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "C9 2D 2F 24" || content.substring(1) == "E7 47 63 63")
  {   digitalWrite(LED_PIN, HIGH); 
      if (content.substring(1) == "C9 2D 2F 24") {
      name="Bhupendra Negi"  ;
      } else {
        name="Employee X";
      }
      Serial.println("Authorized employee");
      Serial.println();
      display.clearDisplay();
      display.setCursor(5,0);
      display.print("Authenticated...");
      display.display();
      delay(2000);
      reset_display();
      // push data to IOT cloud 
       if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection state
      pushToCloud(content.substring(1),name);   
      } else  {
        Serial.println("Trouble connecting to Internet....");
      }
  }  
  else {
      Serial.println("Wrong Card....");
      Serial.println();
      display.clearDisplay();
      display.setCursor(5,0);
      display.print("Wrong Card....");
      display.display();
      delay(2000);
      reset_display();
  }   
  
}

void reset_display() {
  display.clearDisplay();         
  display.setCursor(5,5);  
  display.print("Show Your Card...");
  digitalWrite(LED_PIN, LOW); 
  display.display();  
}

void pushToCloud(String card, String name) {
       // update data to field 
     HTTPClient http;  //Declare an object of class HTTPClient
    Serial.println("Card value pushed:");    
    Serial.println(card);
     http.begin((String)"http://api.thingspeak.com/update?api_key="+KEY_thinkspeak+"&field1="+card+"&field2="+name+"&field3=Veg");
    int httpCode = http.GET();                                                                  //Send the request
    Serial.println("HTTP CODE :");    
    Serial.print(httpCode);
    if (httpCode > 0) { //Check the returning code
      Serial.println("http code > 0");
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                  //Print the response payload    
    }
    http.end();   //Close connection 
  
 }
