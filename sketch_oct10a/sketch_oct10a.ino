#include <HC020K.h>
#include <DRV8835.h>

DRV8835 motors(8, 6, 7, 5, true);
HC020K enc(2);

void count(){
    enc.countTicks();
}

void setup() {
  // put your setup code here, to run once:
  enc.init(&count);
  enc.setDirection(HC020K::FORWARD);
  motors.init();
  motors.setInverted(1, true);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Rotations: ");
  Serial.print(enc.getTicks());
  Serial.print("\n");
}
