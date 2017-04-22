/*

  Example code for the Adafruit RGB Character LCD Shield and Library

  This code displays text on the shield, and also reads the buttons on the keypad.
  When a button is pressed, the backlight changes color.

*/
// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

#include <EVs_NXTLight.h>
#include <EVShield.h>


// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define WHITE 0x7

//Powers
#define CPowerForward 30
#define CPowerReverse 100

//Rotations
#define CRotation 1

//Inputs
#define CMotorL SH_Motor_1
#define CMotorR SH_Motor_2
#define CRLS GRLightSensor
#define CCLS GCLightSensor
#define CLLS GLLightSensor

//Directions
#define CDirectionForward SH_Direction_Reverse
#define CDirectionReverse SH_Direction_Forward

//Objects8
EVShield          GEVShield(0x34, 0x36);
EVs_NXTLight GRLightSensor;
EVs_NXTLight GLLightSensor;
EVs_NXTLight GCLightSensor;

void setup() {
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  GEVShield.init( SH_HardwareI2C );
  GEVShield.bank_a.motorReset();
  GRLightSensor.init(&GEVShield, SH_BAS1);
  GRLightSensor.setReflected();
  GCLightSensor.init(&GEVShield, SH_BBS2);
  GCLightSensor.setReflected();
  GLLightSensor.init(&GEVShield, SH_BBS1);
  GLLightSensor.setReflected();

  /* // Print a message to the LCD. We track how long it takes since
    // this library has been optimized a bit and we're proud of it :)
    int time = millis();
    lcd.print("Hello, world!");
    time = millis() - time;
    Serial.print("Took "); Serial.print(time); Serial.println(" ms");
    lcd.setBacklight(WHITE);*/

  Serial.println ("Press GO button to continue");
  while (GEVShield.getButtonState(BTN_GO) != true)
  {
    delay(50);
  }
}

uint8_t i = 0;
void loop() {

  int LLightValueLeft;
  int LLightValueRight;
  LLightValueLeft = CLLS.readRaw();
  LLightValueRight = CRLS.readRaw();

  int time = millis();
  lcd.setCursor(0, 0);
  lcd.print("Left sensor:");
  lcd.setCursor(13, 0);
  lcd.print(LLightValueLeft);
  delay(50);
  lcd.setCursor(0, 1);
  lcd.print("Right sensor:");
  lcd.print(LLightValueRight);
  time = millis() - time;
  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
  lcd.setBacklight(WHITE);

  delay(50);


}
