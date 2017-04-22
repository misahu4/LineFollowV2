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
EVShield          GEVShield(0x34,0x36);
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
    Serial.println("GO");
}

uint8_t i=0;

void OffMotor (int Port)
{
GEVShield.bank_b.motorStop(Port, SH_Next_Action_Brake);
}

void RunMotor(int Port, int ForwardBack , int Speed) {
    GEVShield.bank_a.motorRunUnlimited(
        Port, 
        ForwardBack, 
        Speed);

}

void RunMotorRotation(int Port, int ForwardBack , int Speed, int Rotation) {
    GEVShield.bank_b.motorRunRotations(
        Port, 
        ForwardBack, 
        Speed,
        Rotation, 
        SH_Completion_Wait_For,
        SH_Next_Action_BrakeHold);
}

void RunTwoMotors(int MotorPort1, int MotorPort2, int ForwardBack , int Speed) {
RunMotor(MotorPort1, 
        ForwardBack, 
        Speed);
delay(1);
RunMotor(MotorPort2, 
        ForwardBack, 
        Speed);
}

void RightSensorLineFollow()
{
    int LLightValue;
    int LThreshold = 650; // You will have to set this value after calibration
    // i8nt LMotorPowerInside  =  1; // This value will depend on the battery level. Uncomment for sharper turns. 

    LLightValue = CRLS.readRaw();


      if (LLightValue < LThreshold){
        RunMotor(CMotorL, CDirectionForward, CPowerForward);
        RunMotor(CMotorR, CDirectionReverse, CPowerReverse);
        // GEVShield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, LMotorPowerInside); // Comment the line above, and uncomment this line for sharper turns
    } else {
       RunMotor(CMotorL, CDirectionReverse, CPowerReverse);
       RunMotor(CMotorR, CDirectionForward, CPowerForward);
    }
        Serial.println (LLightValue);
      
}


void LeftSensorLineFollow()
{
    int LLightValue;
    int LThreshold = 650; // You will have to set this value after calibration
    // int LMotorPowerInside  =  1; // This value will depend on the battery level. Uncomment for sharper turns. 

    LLightValue = CLLS.readRaw();


      if (LLightValue < LThreshold){
        RunMotor(CMotorR, CDirectionForward, CPowerForward);
        RunMotor(CMotorL, CDirectionReverse, CPowerReverse);
        // GEVShield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, LMotorPowerInside); // Comment the line above, and uncomment this line for sharper turns
    } else {
       RunMotor(CMotorR, CDirectionReverse, CPowerReverse);
       RunMotor(CMotorL, CDirectionForward, CPowerForward);
    }
        Serial.println (LLightValue);
      
}

void CheckLight()
{
  int LLightValueLeft;
  int LLightValueRight;
  int LThreshold = 660;

  //NOTE: 1 = black, white = 0
  
}

void TwoSensorLineFollow()
{
    // int LMotorPowerInside  =  1; // This value will depend on the battery level. Uncomment for sharper turns. 
    int LLightValueLeft;
    int LLightValueRight;
    int LLightValueCentre;
    LLightValueLeft = CLLS.readRaw();
    LLightValueRight = CRLS.readRaw();
    LLightValueCentre = CCLS.readRaw();
    int LThreshold;
    LThreshold = 650;
if((LLightValueCentre <690) || (LLightValueCentre > 710))
{    
    if ((LLightValueLeft <= LThreshold) & (LLightValueRight <= LThreshold))
    {
      RunMotor(CMotorR, CDirectionForward, CPowerForward);
      RunMotor(CMotorL, CDirectionForward, CPowerForward);
      Serial.println(" White white ");
    }
    else if ((LLightValueLeft > LThreshold) & (LLightValueRight <= LThreshold))
    {
      RunMotor(CMotorL, CDirectionForward, CPowerForward);
      RunMotor(CMotorR, CDirectionReverse, CPowerReverse);
      Serial.println(" black white ");
    }
    else if ((LLightValueLeft <= LThreshold) & (LLightValueRight > LThreshold))
    {
      RunMotor(CMotorR, CDirectionForward, CPowerForward);
      RunMotor(CMotorL, CDirectionReverse, CPowerReverse);
      Serial.println(" white black ");
    }

  /*  else if((LLightValueCentre <690) || (LLightValueCentre > 710))
    {
      lcd.setCursor(0, 0);
      lcd.print("   finished  ");
      OffMotor(CMotorL);
      OffMotor(CMotorR);
      delay(10000);  
    }*/

    else
  {
   OffMotor(CMotorL);
   OffMotor(CMotorR);
   Serial.println(" Black black ");
  }  
  

}
void DisplayLight() {

int LLightValueLeft;
int LLightValueRight;
    LLightValueLeft = CLLS.readRaw();
    LLightValueRight = CRLS.readRaw();    

int time = millis();
  lcd.setCursor(0, 0);
  lcd.print("Left sensor:");
  lcd.setCursor(13,0);
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


void ClearLCD()
{
 lcd.setCursor(0, 0);
 lcd.print("             ");
 lcd.setCursor(0, 1);
 lcd.print("              ");
}


void loop()
{
 /*lcd.setCursor(0, 0);
 lcd.print("L=LightValues");
 lcd.setCursor(0, 1);
 lcd.print("R=LineFollow");*/


 TwoSensorLineFollow();
  
  /*if (GEVShield.getButtonState(BTN_LEFT) != true)

    {
      //DisplayLight();
    }
   else if (GEVShield.getButtonState(BTN_RIGHT) != true)
    {
      TwoSensorLineFollow();
    } 
   else
   {
    delay(20); 
   }
 ClearLCD();*/
 

}

//1ST JOB: 2 calibration values
//PID algo2rithm
