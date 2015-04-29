#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <MAX6675.h>
#include <SPI.h>
#include <Wire.h>


/*
  Single_Temp.pde - Example using the MAX6675 Library.
  Created by Ryan McLaughlin <ryanjmclaughlin@gmail.com>
*/

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

static const unsigned char PROGMEM turbo16_glcd_bmp[] =
{B01111111, B11100000,
B01111110, B10110000,
B01111100, B10011000,
B01111010, B10101100,
B00010001, B11000100,
B00011111, B01111100,
B00010001, B11000100,
B00011010, B10101111,
B00001100, B10011111,
B00000110, B10111111,
B00000011, B11111111,
B11101111, B11111111,
B10011011, B01100010,
B11101011, B01111010,
B10011011, B01001010,
B11111111, B11111010 };

static const unsigned char PROGMEM turbo32_glcd_bmp[] = 
{ B00111111, B11111111, B11111100, B00000000,
  B00111111, B11111111, B11111100, B00000000,
  B00111111, B11111100, B11001111, B00000000,
  B00111111, B11111100, B11001111, B00000000,
  B00111111, B11110000, B11000011, B11000000,
  B00111111, B11110000, B11000011, B11000000,
  B00111111, B11001100, B11001100, B11110000,
  B00111111, B11001100, B11001100, B11110000,
  B00000011, B00000011, B11110000, B00110000,
  B00000011, B00000011, B11110000, B00110000,
  B00000011, B11111111, B00111111, B11110000,
  B00000011, B11111111, B00111111, B11110000,
  B00000011, B00000011, B11110000, B00110000,
  B00000011, B00000011, B11110000, B00110000,
  B00000011, B11001100, B11001100, B11111111,
  B00000011, B11001100, B11001100, B11111111,
  B00000000, B11110000, B11000011, B11111111,
  B00000000, B11110000, B11000011, B11111111,
  B00000000, B00111100, B11001111, B11111111,
  B00000000, B00111100, B11001111, B11111111,
  B00000000, B00001111, B11111111, B11111111,
  B00000000, B00001111, B11111111, B11111111,
  B00000000, B00000000, B00000000, B00000000,
  B11111100, B11111111, B11111111, B11111111,
  B11111100, B11111111, B11111111, B11111111,
  B11000011, B11001111, B00111100, B00001100,
  B11000011, B11001111, B00111100, B00001100,
  B11111100, B11001111, B00111111, B11001100,
  B11111100, B11001111, B00111111, B11001100,
  B11000011, B11001111, B00110000, B11001100,
  B11000011, B11001111, B00110000, B11001100,
  B11111111, B11111111, B11111111, B11001100 };

int pinCS0 = 11;         // CS pin on MAX6675
int pinSO = 13;          // SO pin of MAX6675
int pinSCK = 12;         // SCK pin of MAX6675
int units = 2;        // Units to readout temp (0 = ÀöF, 1 = ÀöC)
float error = 0.0;    // Temperature compensation error
float temp_out = 0.0; // Temperature output varible

int absolutePressureSensorPin = 0;
float absolutePressure = 0.0;

MAX6675 temp0(pinCS0,pinSO,pinSCK,units);

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(500);
  display.clearDisplay();
  display.display();
  
  // draw a single pixel
  display.drawPixel(10, 10, WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop() {
  temp_out = temp0.read_temp();  // Read the temp 5 times and return the average value to the var
  absolutePressure = .00488 * analogRead(absolutePressureSensorPin);
  
  display.clearDisplay();
  
  
  String boost = "";
  boost += (int)absolutePressure;
  boost += "PSI";
  
  String egt = "";
  egt += (int)((temp_out - 30)/2);
  egt += "C";
  
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  WriteString(display, boost);
  display.println(); 
  WriteString(display, egt);
  display.println();
  display.display();
  
  
  
  delay(5);                    // Wait one second
}

void WriteString(Adafruit_SSD1306 display, String string) {
  int len = string.length();
  for(int i = 0; i < len; i++) {
    display.write(string.charAt(i));
  }
}
