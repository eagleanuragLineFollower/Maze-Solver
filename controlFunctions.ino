void frontCrashTest()
{
  
  int currDist = analogRead(FRONTSENSOR) - baseLevelF;
  //Serial.println(currDist);
  if (currDist > 200)
  {
     //Serial.println("Front alert");
     analogWrite(PWM1, 0);
     analogWrite(PWM2, 0);
     //delay(2000);
     if ((analogRead(RIGHTSENSOR) - analogRead(LEFTSENSOR)) > 300)
     {
      //Serial.println("Turning left");
      turn90(1);
     }
     else if ((analogRead(RIGHTSENSOR) - analogRead(LEFTSENSOR)) < -300)
     {
      //Serial.println("Turning right");
      turn90(0);
     }
     else if (abs(analogRead(RIGHTSENSOR) - analogRead(LEFTSENSOR)) < 40)
     {
        lMSpeed =0;
        rMSpeed =0;
        while(true)
        {
          ;     
        }
     }
  }
  
}

void turn90(int dir)
{
  if (dir == 1){  //turn left
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(PWM1, 0);
    analogWrite(PWM2, 90);
    delay(700);
  }
  else //turn right
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM1, 90);
    analogWrite(PWM2, 0);
    delay(700);
  }
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(PWM1, lMSpeed);
  analogWrite(PWM2, rMSpeed);
}

void sensorTest()
{
  Serial.print("Left ");
  Serial.println(analogRead(LEFTSENSOR)-baseLevelL);
  Serial.print("Right ");
  Serial.println(analogRead(RIGHTSENSOR)-baseLevelR);
  Serial.print("Front ");
  Serial.println(analogRead(FRONTSENSOR)-baseLevelF);
//    Serial.print("Raw sensor Value : ");
//    Serial.println(analogRead(FRONTSENSOR));
//    Serial.print("Normalized value: ");
//    Serial.println(analogRead(FRONTSENSOR)-baseLevelF);
    delay(900);
}

void propControl()
{
  //positiveCorrection implies we are too far right, negative implies too far left
  int currDist2 = analogRead(FRONTSENSOR) - baseLevelF;
  double correction = 0;
  double pConstant = 0.02;  //0.02
  double dConstant = 0.005;
  int lErr = analogRead(LEFTSENSOR)-baseLevelL;
  int rErr = analogRead(RIGHTSENSOR)-baseLevelR;
  int err = lErr - rErr; 
  double dErr = (err-prevErr)/0.1;
  correction = (pConstant*(abs(err))) + (dConstant*((dErr)));
  if (err > 20)
  {    
    rMSpeed -= correction;
    lMSpeed += correction;
  }
  else if (err < -60) {
    lMSpeed -= correction;
    rMSpeed += correction;
  } else
  {
    rMSpeed += 5;
    lMSpeed = rMSpeed;
  }
  if(currDist2 >700 && lErr > 600){
    lMSpeed -= correction * 2;
    rMSpeed += correction * 2;
  }
  prevErr = err;
  //Serial.print("Error: ");
  //Serial.println(err);
  //Serial.print("Correction: ");
  //Serial.println(correction);
  if (lMSpeed < minlMSpeed) {
    lMSpeed = minlMSpeed;
  }
  if (lMSpeed > maxlMSpeed){
    lMSpeed = maxlMSpeed;
  }
  if (rMSpeed < minrMSpeed) {
    rMSpeed = minrMSpeed;
  }
  if (rMSpeed > maxrMSpeed){
    rMSpeed = maxrMSpeed;
  }
//  Serial.print("Motor speeds:");
//  Serial.println(lMSpeed);
//  Serial.println(rMSpeed);
//  Serial.println();
//  Serial.println();
//  Serial.println();
//  Serial.println();
}
