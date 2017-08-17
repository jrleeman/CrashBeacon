int buzzerPin = 3; // PWM pin the buzzer is connected to
int armPin = 4; // Arming wire pin
int fall_duration = 0; // Fall duration counter
int fall_duration_threshold = 2; // Threshold for alarm activation

void setup() {
  Bean.setAccelerationRange(4); // +/- 4g
  Bean.enableMotionEvent(LOW_G_EVENT); // Turn on fall detection
  Bean.setLed(0,0,0); // Make sure the LED is off
  pinMode(buzzerPin,OUTPUT); // Make the buzzer an output
  pinMode(armPin, INPUT_PULLUP); // Make the arming pin a pulled up input
 }

void loop() {
  // If we're disarmed, sleep for a while
  if (digitalRead(armPin) ==LOW){Bean.sleep(1000);}

  // Armed and running!
  else {
    turnOnLedBasedOnBatteryLevel();
    checkForFall();

    // We've been falling for awhile, start the beacon
    if (fall_duration >= fall_duration_threshold){state_alarm();}

    Bean.setLed(0,0,0); // Turn off the LED
    Bean.sleep(500); // Sleep for half a second
  }
}

void turnOnLedBasedOnBatteryLevel(){
  if (Bean.getBatteryLevel() >= 50){Bean.setLed(0, 255, 0);}
  else if (Bean.getBatteryLevel() >= 20){Bean.setLed(75, 255, 0);}
  else {Bean.setLed(255, 0, 0);}
}

void checkForFall() {
  if(Bean.checkMotionEvent(LOW_G_EVENT)){fall_duration += 1;}
  else {fall_duration = 0;}
}

void state_alarm() {
  // Alarm until the arming plug is re-inserted
  while(true) {
    Bean.setLed(255,0,0); // Red LED
    playTones();
    Bean.setLed(0,0,0); // Turn off LED
    if (digitalRead(armPin)==LOW){return;} // Return to main loop if disarmed
    Bean.sleep(5000); // Sleep between tone cycles
  }
}

void playTones() {
  for (int i=0; i<3; i++){
    tone(buzzerPin, 880, 1000);
    delay(1100);
    noTone(buzzerPin);
    tone(buzzerPin, 440, 1000);
    delay(1100);
    noTone(buzzerPin);
  }
}
