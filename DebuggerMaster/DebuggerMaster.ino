//Libraries
#include <EVs_NXTLight.h>
#include <EVShield.h>

//Powers
#define CPowerForward 50
#define CPowerReverse 40

//Rotations
#define CRotation 1

//Inputs
#define CMotorL SH_Motor_1
#define CMotorR SH_Motor_2
#define CMotorLR SH_Motor_Both
/*#define CRLS GRLightSensor
#define CCLS GCLightSensor
#define CLLS GLLightSensor

//Directions
#define CDirectionForward SH_Direction_Reverse
#define CDirectionReverse SH_Direction_Forward

//Objects8*/
EVShield          GEVShield(0x34,0x36);
/*EVs_NXTLight GRLightSensor;
EVs_NXTLight GLLightSensor;
EVs_NXTLight GCLightSensor;*/

void setup()
{
    Serial.begin(9600);
    
    //initialisations
    GEVShield.init( SH_HardwareI2C );
    GEVShield.bank_a.motorReset();
    GEVShield.bank_b.motorReset();
   /* GRLightSensor.init(&GEVShield, SH_BAS1);
    GRLightSensor.setReflected();
    GCLightSensor.init(&GEVShield, SH_BBS2);
    GCLightSensor.setReflected();
    GLLightSensor.init(&GEVShield, SH_BBS1);
    GLLightSensor.setReflected();*/


    Serial.println ("Press GO button to continue");
    while (GEVShield.getButtonState(BTN_GO) != true)
    {
      delay(50);
    }
}
/*void lineFollowLeft()
{
  GEVShield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, 50);
  GEVShield.bank_a.motorRunUnlimited(SH_Motor_2, SH_Direction_Reverse, 20);
}

void lineFollowRight()
{
  GEVShield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Reverse, 50);
  GEVShield.bank_a.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, 20);
}*/

void loop() {
  // put your main code here, to run repeatedly:
  GEVShield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, 50);
  GEVShield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, 50);


}
