#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <MFRC522.h>

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


#define RST_PIN         D3          // Configurable, see typical pin layout above
#define SS_PIN          D4         // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

Adafruit_SSD1306 display = Adafruit_SSD1306();

void setup()
{
  Serial.begin(9600);// For nodemcu

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
  delay(3000);
  
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
  if (content.substring(1) == "C9 2D 2F 24")
  {
      Serial.println("Authorized employee");
      Serial.println();
      display.clearDisplay();
      display.setCursor(5,0);
      display.print("Authenticated...");
       display.display();
      delay(3000);
       display.clearDisplay();
          
  display.setCursor(5,5);
  
  display.print("Show Your Card...");
  display.display();
    
  }
  
  else {
      Serial.println("Wrong Card....");
      Serial.println();
      display.clearDisplay();
      display.setCursor(5,0);
      display.print("Wrong Card....");
      display.display();
      delay(3000);
      display.clearDisplay();          
      display.setCursor(5,5);
      display.print("Show Your Card...");
      display.display();
  }
  
  
 
  
}
