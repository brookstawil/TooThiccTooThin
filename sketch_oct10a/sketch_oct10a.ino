#include <HC020K.h>
#include <DRV8835.h>

DRV8835 motors(8, 6, 7, 5, true);
HC020K LeftEncoder(12);
HC020K RightEncoder(2);

void countLeft(){
    LeftEncoder.countTicks();
}


void countRight(){
    RightEncoder.countTicks();
}

void setup() {
  // put your setup code here, to run once:
  LeftEncoder.init(&countLeft);
  RightEncoder.init(&countRight);
  LeftEncoder.setDirection(HC020K::FORWARD);
  RightEncoder.setDirection(HC020K::FORWARD);
  motors.init();
  motors.setInverted(1, true);

  Serial.begin(9600);
}

void loop() {
  motors.setSpeed(0, 200);
  motors.setSpeed(1, 200);
  
  // put your main code here, to run repeatedly:
  Serial.print("Left Rotations: ");
  Serial.print(LeftEncoder.getTicks());
  Serial.print("\tRight Rotations: ");
  Serial.print(RightEncoder.getTicks());
  Serial.print("\n");
}
