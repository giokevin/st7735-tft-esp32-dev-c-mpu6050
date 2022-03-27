
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

// TFT_LED // 3.3V +
// TFT_SCK // GPIO 18
#define TFT_DC 2 // GPIO 02 // (A0)
#define TFT_RST 14 // GPIO 14
#define TFT_CS 17 // GPIO 17
// TFT_GND // GND
// TFT_VCC // 3.3V +

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {
  
  while (!Serial)
    delay(10); 
  
  Serial.begin(9600);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  
  Serial.println("MPU6050 Found!");

  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setTextColor(ST77XX_WHITE);
  testdrawtext("Initializing...", ST77XX_WHITE, 0, 0, 1);
  
  delay(1000);
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  
  delay(100);
}

void loop() {
  
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  /*Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");*/

  char tempChar[10];     
  float finalTemp = temp.temperature - 4.75;
  dtostrf(finalTemp, 5, 0, tempChar);
  
  testdrawtext(charVal, ST77XX_WHITE, -100, 65, 6);

  tft.setTextSize(2);
  tft.setCursor(80, 76);
  tft.print("o");
  tft.setTextSize(4);
  tft.setCursor(96, 80);
  tft.print("C");
  
  Serial.print(finalTemp);
  Serial.println(" degC");

  delay(5000);
}


void testdrawtext(char *text, uint16_t color, int cursorX, int cursorY, int stringSize) {
  tft.setTextSize(stringSize);
  tft.setCursor(cursorX, cursorY);
  tft.setTextWrap(true);
  tft.fillScreen(ST77XX_BLACK);
  tft.print(text);
}
