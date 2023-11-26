# R503-fingerprint-sensor-and-SSD1306-display-on-Arduino-device
An Arduino sketch using an R503 sensor and SSD1306 128 X 2 display. An initial attempt which works fine but wins no coding beauty prizes :)
Please note:
 - Arduinos Libraries
   - To get this sketch to complile in the Arduino IDE, you need to import the following libraries
     - "SSD1306Ascii" - Text display on small monochrome OLED Modules (by Bill Greiman)
     - "Adafruit Fingerprint Sensor library" (by Adafruit)
- Connections
  - The finger print display is powered with the 3.3v line and 0V (ground)
  - The finger print sensor communicates via digital pins 2 and 3 (See pdf for more info) 
  - The SSD1306 display is powered with the 5v line and 0V (ground)
  - The SSD1306 display communicates with the Arduino's I2C pins - A4(SDA) and A5(SCL). 
