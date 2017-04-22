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
#define CRLS GRLightSensor
#define CCLS GCLightSensor
#define CLLS GLLightSensor

//Directions
#define CDirectionForward SH_Direction_Reverse
#define CDirectionReverse SH_Direction_Forward

//Objects
EVShield          GEVShield(0x34,0x36);
EVs_NXTLight GRLightSensor;
EVs_NXTLight GLLightSensor;
EVs_NXTLight GCLightSensor;

void setup()
{
    Serial.begin(9600);
    
    //initialisations
    GEVShield.init( SH_HardwareI2C );
    GEVShield.bank_b.motorReset();
    GRLightSensor.init(&GEVShield, SH_BAS1);
    GRLightSensor.setReflected();
    GCLightSensor.init(&GEVShield, SH_BBS2);
    GCLightSensor.setReflected();
    GLLightSensor.init(&GEVShield, SH_BBS1);
    GLLightSensor.setReflected();


    Serial.println ("Press GO button to continue");
    while (GEVShield.getButtonState(BTN_GO) != true)
    {
      delay(50);
    }
}

void loop() {
  // put your main code here, to run repeatedly:

  while (GEVShield.getButtonState(BTN_LEFT) != true)
    {
       GEVShield.bank_b.motorRunUnlimited(SH_Motor_1, 
        CDirectionForward, 
        50);
delay(1);
 GEVShield.bank_b.motorRunUnlimited(SH_Motor_2, 
        CDirectionForward, 
        50);
    }

           GEVShield.bank_b.motorRunUnlimited(SH_Motor_1, 
        CDirectionForward, 
        50);
delay(1);
 GEVShield.bank_b.motorRunUnlimited(SH_Motor_2, 
        CDirectionReverse, 
        50);





}
