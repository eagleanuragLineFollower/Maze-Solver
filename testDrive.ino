#define PWM1 3
#define PWM2 9
#define IN1 4
#define IN2 5
#define IN3 7
#define IN4 8
#define FRONTSENSOR A5
#define LEFTSENSOR 18
#define RIGHTSENSOR 17

int baseLevelF;
int baseLevelL;
int baseLevelR;
int rMSpeed;
int lMSpeed;
int prevErr;
int maxrMSpeed;
int maxlMSpeed;
int minrMSpeed;
int minlMSpeed;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(FRONTSENSOR, INPUT);
  pinMode(LEFTSENSOR,INPUT);
  pinMode(RIGHTSENSOR,INPUT);
  baseLevelF = 0;
  baseLevelR = 0;
  baseLevelL = 0;
  rMSpeed = 60;
  lMSpeed = 60;
  prevErr = 0;
  maxrMSpeed = 110;
  maxlMSpeed = 110;
  minrMSpeed = 50;
  minlMSpeed = 50;
  for (int i = 0; i < 25; i++)
  {
    baseLevelF += analogRead(FRONTSENSOR);
    baseLevelR += analogRead(RIGHTSENSOR);
    baseLevelL += analogRead(LEFTSENSOR);
    
    delay(15 );
  }
  baseLevelF /= 25;
  baseLevelR /= 25;
  baseLevelL /= 25;
  Serial.println(baseLevelF);
}

void drive()
{
  //frontCrashTest();
  propControl();
  
  analogWrite(PWM1, lMSpeed);
  analogWrite(PWM2, rMSpeed);
  delay(100);
}



void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //sensorTest();
  //frontCrashTest();
  drive();
}
