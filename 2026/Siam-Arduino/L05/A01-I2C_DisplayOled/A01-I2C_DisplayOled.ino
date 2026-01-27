#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//posizione ball
int x = 0;
int y = 32;
int dx = 2;
int dy = 1;

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println("Hello!");

  display.drawLine(1, 1, 126, 1, SSD1306_WHITE);

  display.display(); 
  delay(1000);    
}

void loop() {
  x = x + dx;
  if ((x >= 123) || (x <= 0) ) {
    dx = -dx;
  }
  
  y = y + dy;
  if ((y >= 59) || (y <= 0)) {
    dy = -dy;
  }
  display.clearDisplay();
  display.fillRect(x, y, 5, 5, SSD1306_WHITE);  
  display.display();
  delay(20);
}
