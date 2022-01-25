#include <Arduino.h>
#include <TMC2209.h>

HardwareSerial & serial_stream = Serial1;

const long BAUD = 115200;
const int DELAY = 200;
const uint8_t RUN_CURRENT_PERCENT = 40;
const int32_t VELOCITY = 20000;
const uint8_t STALL_GUARD_THRESHOLD = 50;


// Instantiate TMC2209
TMC2209 stepper_driver;


void setup()
{
  Serial.begin(BAUD);

  stepper_driver.setup(serial_stream,TMC2209::SERIAL_ADDRESS_0);

  if (stepper_driver.communicating())
  {
    Serial.println("Communicating with stepper driver!");
    Serial.println("");
  }
  else
  {
    Serial.println("Not communicating with stepper driver!");
    return;
  }

  stepper_driver.setRunCurrent(RUN_CURRENT_PERCENT);
  stepper_driver.setStallGuardThreshold(STALL_GUARD_THRESHOLD);
  stepper_driver.enable();
  stepper_driver.moveAtVelocity(VELOCITY);
}

void loop()
{
  if (not stepper_driver.communicating())
  {
    Serial.println("Not communicating with stepper driver!");
    return;
  }

  Serial.print("run_current_percent = ");
  Serial.println(RUN_CURRENT_PERCENT);

  Serial.print("stall_guard_threshold = ");
  Serial.println(STALL_GUARD_THRESHOLD);

  uint16_t stall_guard_result = stepper_driver.getStallGuardResult();
  Serial.print("stall_guard_result = ");
  Serial.println(stall_guard_result);

  Serial.println("");
  delay(DELAY);

}
