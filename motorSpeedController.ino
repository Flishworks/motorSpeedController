const int motorOut=0;
const int pedalIn=1;
const int battIn=3;
int motorSpeed=0; // 0 to 255
int pedalVal = 0; // 0 to 1024
int lastPedalVal = 0;
int threshold = 50;// 0 to 1024 limit the rate at which the motor can decelerate. Higher number=higher rate. time it will take to do a full decel is 256/threshold seconds
const int battCutoff=700; //battery level at which to shut down system. depends on voltage divider. for 1/3 voltage divider on input from 12 volt pack with a cutoff at 10 volts, cutoff should be 3.33V or 3.33/5*1024=682
int battVal=0;


void setup() {
pinMode(Motor, OUTPUT);
}


void loop() { 
//battery monitor
  battVal=analogRead(battIn);
  if (battVal>battCutoff){ //Battery Monitor OK
    pedalVal=analogRead(pedalIn);
  }
  else{ //Battery Monitor not OK. Shut 'er down.
    pedalVal=0;
  }
  
//limit deceleration
  if( pedalVal > lastPedalVal-threshold ){ //accelerating or decelerating within threshold. allow accel/decel at pedal rate.
    lastPedalVal=pedalVal;
    motorSpeed=pedalVal/4; //adjust from speed input (0-1023) to PWM output (0-255)
  }
  else{//pedal moving faster than threshold rate. limit rate.
    lastPedalVal=lastPedalVal-threshold;
    motorSpeed=lastPedalVal/4;
  }
  
  analogWrite(motorOut,motorSpeed);
  delay(250); // 1/4 second delay in between reads for human compatible timing
}
