#include <DRV8835.h>
#include <HC020K.h>
#include <NewPing.h>

#define ENC_1_PIN 2
#define ENC_2_PIN 3
#define TRIGGER_PIN  12
#define ECHO_PIN     11

#define KP 1
#define MAX_DISTANCE 200

/**
 * EXTREMELY IMPORTANT!!!
 * 
 * When uploading code to your Arduino, make sure it is NOT getting power from the 9V
 * and it is only getting power from USB
 * Things become screwy if it gets power from both...
 */

// Object instantiation in C++ (no new keyword needed)
DRV8835 motors(7, 5, 8, 6, 4);
HC020K enc1(ENC_1_PIN);
HC020K enc2(ENC_2_PIN);

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Treat these as magic for now, for more information, look at interrupt handlers
// Also look at function pointers for more information on how to pass this to the encoder class
void counterL() {
  enc1.countTicks();
}

void counterR() {
  enc2.countTicks();
}

void setup() {
  motors.init();
  motors.setInverted(1, true);
  
  enc1.init(&counterL);
  enc2.init(&counterR);
  
  enc1.setDirection(HC020K::FORWARD);
  enc2.setDirection(HC020K::FORWARD);
  
   Serial.begin(115200); // for sensors
 
  Serial.begin(9600);
  Serial.print("Starting");
  delay(1000);
}

int masterSpeed = 150;
int slaveSpeed = 150;

int p;
int scaledP;

int output;

void loop() {
  // There is probably a better way to print this using string formatting but I'm writing this pretty fast...
  Serial.print(" Step: \t");
  Serial.print(enc1.getTicks(), DEC);
  Serial.print("\t");
  Serial.print(enc2.getTicks(), DEC);

  //Calculate p = encL - encR
  p = enc1.getTicks() - enc2.getTicks();
  scaledP = KP*p;

  Serial.print("\t Proportion: \t");
  Serial.print(p, DEC);
  Serial.println("\t");

  output = scaledP;

  slaveSpeed = abs(slaveSpeed - output);

  Serial.print("Master Speed: \t");
  Serial.print(masterSpeed, DEC);
  Serial.print(" Slave Speed: \t");
  Serial.print(slaveSpeed, DEC);
  
  motors.setSpeed(0, masterSpeed);
  motors.setSpeed(1, slaveSpeed);
  //delay(1000);
  //for (int i=0; i<2; i++) {
  //  motors.setSpeed(i, 0);
  //}
  delay(200);

    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm());
    Serial.println("cm");

  

  // Uncomment these to see the motors move in all four direction combinations
//  motors.setSpeed(0, speed);
//  motors.setSpeed(1, -speed);
//  delay(1000);
//  for (int i=0; i<2; i++) {
//    motors.setSpeed(i, 0);
//  }
//  delay(500);
//  motors.setSpeed(0, -speed);
//  motors.setSpeed(1, -speed);
//  delay(1000);
//  for (int i=0; i<2; i++) {
//    motors.setSpeed(i, 0);
//  }
//  delay(500);
//  motors.setSpeed(0, -speed);
//  motors.setSpeed(1, speed);
//  delay(1000);
//  for (int i=0; i<2; i++) {
//    motors.setSpeed(i, 0);
//  }
//  delay(2000);
}
