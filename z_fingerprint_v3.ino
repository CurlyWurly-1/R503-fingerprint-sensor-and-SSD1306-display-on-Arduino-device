/***************************************************
  This is an example sketch for a optical R503  Fingerprint sensor
  matched with a ssd1306 display  
 ****************************************************/

#include "ssd1306.h"

#include <Adafruit_Fingerprint.h>

SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
unsigned long trigTime = millis();
unsigned long currentTime = millis();
int errCount = 0;
const long interval = 2500;
bool sensorOK = false;

//***************************************************************************
// setup()
//***************************************************************************
void setup()
{
    /* Replace the line below with ssd1306_128x32_i2c_init() if you need to use 128x32 display */
  delay(100);
  ssd1306_128x32_i2c_init();
  delay(100);
  ssd1306_fillScreen(0x00);
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_printFixed (0,  0, "Setting up....", STYLE_BOLD);
  ssd1306_printFixed (0,  8, "Please Wait", STYLE_BOLD);
  
  ;  
  Serial.begin(9600);
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");
  ssd1306_printFixed (0, 24, "Finger Sensor Test", STYLE_BOLD);
  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(100);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
    ssd1306_printFixed (0, 24, "Found Finger sensor", STYLE_BOLD);
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    ssd1306_printFixed (0, 24, "Did not find Finger sensor", STYLE_BOLD);
    while (1) { delay(1); }
  }

  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);

  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
    ssd1306_printFixed (0, 24, "No data - please enroll", STYLE_BOLD);
    
  }
  else {
    Serial.println("Waiting for valid finger...");
    Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
    sensorOK = true;
  }

  if (sensorOK == true) {
    ssd1306_fillScreen(0x00);
    ssd1306_setFixedFont(ssd1306xled_font6x8);
//    ssd1306_printFixed (0,  0, "FINGER PRINT READER", STYLE_NORMAL);
//    ssd1306_printFixed (0,  8, "Put your finger here", STYLE_BOLD);
    ssd1306_printFixedN (0,  0, "Please use", STYLE_BOLD, FONT_SIZE_2X);
    ssd1306_printFixedN (0, 16, "Sensor    ", STYLE_BOLD, FONT_SIZE_2X);
  }


}

//***************************************************************************
// void loop()
//***************************************************************************
void loop()                     // run over and over again
{
  if (sensorOK = true) {
    getFingerprintID();
    delay(50);            //don't need to run this at full speed.
  };
}

//***************************************************************************
// int getFingerprintID()
//   returns -1 if failed, otherwise returns ID #
//***************************************************************************
int getFingerprintID() {

  currentTime = millis();
  if ((currentTime - trigTime ) >= interval) {
    ssd1306_printFixed (0,  0, "                    ", STYLE_ITALIC);
    ssd1306_printFixed (0,  8, "                    ", STYLE_ITALIC);
    ssd1306_printFixed (0, 16, "                    ", STYLE_ITALIC);
    ssd1306_printFixed (0, 24, "                    ", STYLE_ITALIC);
    ssd1306_printFixedN (0,  0, "Finger       ", STYLE_BOLD, FONT_SIZE_2X);
    ssd1306_printFixedN (0, 16, "Checking     ", STYLE_BOLD, FONT_SIZE_2X);
    trigTime = 0;
    finger.LEDcontrol(FINGERPRINT_LED_OFF, 0, FINGERPRINT_LED_BLUE);
  };
  uint8_t p = finger.getImage();
  
  if (p != FINGERPRINT_OK) {errCount = 0; return -1;};
  
  if ( ((currentTime - trigTime ) >= interval) and trigTime == 0) {
    ssd1306_printFixedN (0,  0, "Finger    ", STYLE_BOLD, FONT_SIZE_2X);
    ssd1306_printFixedN (0, 16, "Checking  ", STYLE_BOLD, FONT_SIZE_2X);
    errCount++;
    if (errCount > 3) {
      errCount = 4;
      finger.LEDcontrol(FINGERPRINT_LED_ON, 1, FINGERPRINT_LED_RED);
    }else{
      finger.LEDcontrol(FINGERPRINT_LED_GRADUAL_ON, 200, FINGERPRINT_LED_PURPLE);
    }
  };
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

//  p = finger.fingerFastSearch();
  p = finger.fingerSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  if ((currentTime - trigTime ) >= interval) {
    trigTime = millis();
    errCount = 0;
    finger.LEDcontrol(FINGERPRINT_LED_OFF, 0, FINGERPRINT_LED_RED);
    finger.LEDcontrol(FINGERPRINT_LED_OFF, 0, FINGERPRINT_LED_PURPLE);
    finger.LEDcontrol(FINGERPRINT_LED_ON, 1, FINGERPRINT_LED_BLUE);
    Serial.print("Found ID #"); Serial.print(finger.fingerID);
    Serial.print(" with confidence of "); Serial.println(finger.confidence);
    String ztext_string = "Finger  " + String(finger.fingerID) + "  ";
    Serial.println(ztext_string);
    ssd1306_printFixedN (0,  0, ztext_string.c_str(), STYLE_BOLD, FONT_SIZE_2X);  
    ssd1306_printFixedN (0, 16, "Detected  ", STYLE_BOLD, FONT_SIZE_2X);

  }
  return finger.fingerID;
}
