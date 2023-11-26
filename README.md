# R503-fingerprint-sensor-and-SSD1306-display-on-Arduino-device
An Arduino sketch using an R503 sensor and SSD1306 128 X 2 display. An initial attempt which works fine but wins no coding beauty prizes :)

To get this sketch to complile in the Arduino IDE, you need to import the following libraries
 - "SSD1306Ascii" - Text display on small monochrome OLED Modules (by Bill Greiman)
 - "Adafruit Fingerprint Sensor library" (by Adafruit)

N.B. The finger print sensor connections are as described in the PDF, aand they use pins A4 and A5 ) 
N.B. The display connection as are using digital pins 1 and 2
N.B. The SSD1306 display is powered by the 5v line
N.B. The finger print display is powered by the 3.3v line
