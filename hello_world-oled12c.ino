#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306();

void setup()
{
  Serial.begin(9600);// For nodemcu
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
  delay(500);
  display.display();
}
void loop()
{
 
  
}
