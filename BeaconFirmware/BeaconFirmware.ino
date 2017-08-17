int buzzerPin=3;
int armPin =4;

static int fall_duration = 0;
static bool fall_detected = false;

void setup() {
  Bean.setAccelerationRange(4);
  Bean.enableMotionEvent(LOW_G_EVENT);
  Bean.setLed(0,0,0);
  pinMode(buzzerPin,OUTPUT);
  pinMode(armPin, INPUT_PULLUP);
 }



void loop() {
  if (digitalRead(armPin) ==LOW){
        Bean.sleep(500);
  } 
   
  else {
    turnOnLedBasedOnBatteryLevel();
     if(Bean.checkMotionEvent(LOW_G_EVENT)){
       fall_detected = true;
       fall_duration += 1;
      }
        
      else {
        fall_detected = false;
        fall_duration = 0;
      }
    
     if (fall_duration == 2){
       state_alarm();
     }
     Bean.setLed(0,0,0);
     Bean.sleep(500);
    }
   }

void turnOnLedBasedOnBatteryLevel(){
    if (Bean.getBatteryLevel() >= 20){
        Bean.setLed(0, 255, 0);
    }
    else {
        Bean.setLed(75, 255, 0);
    }
}

void state_alarm() {
   
    while(true){
        Bean.setLed(255,0,0);
      for (int i=0; i<3; i++){ 
        tone(buzzerPin, 880, 1000);
        delay(1100); 
        noTone(buzzerPin);    
        tone(buzzerPin, 440, 1000);
        delay(1100);   
        noTone(buzzerPin);       
      }
        Bean.setLed(0,0,0);
      if (digitalRead(armPin)==LOW){
            return;
                   }  
      Bean.sleep(5000);
}    
}
