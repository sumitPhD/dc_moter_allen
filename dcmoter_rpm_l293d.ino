#define E1 10  // Enable Pin for motor 1
//#define E2 11  // Enable Pin for motor 2
#define I1 8  // Control pin 1 for motor 1
#define I2 9  // Control pin 2 for motor 1
//#define I3 12  // Control pin 1 for motor 2
//#define I4 13  // Control pin 2 for motor 2

/// defination for rpm measurement - encoder
 int encoderpin = 7;
int n;
int n0;
float t=0;
int rpm;
int x=0;

///defination for pid controller 
double kp =1;
double ki =0;
double kd =0;

double error;
double lastErr;
double errSum;
unsigned long lastTime =0 ; //last time when computed; initialize to zero

double referenceRpm =200;
double uDesired;


 

 
void setup() {
 
    pinMode(E1, OUTPUT);
  //  pinMode(E2, OUTPUT);
 
    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
    //pinMode(I3, OUTPUT);
    //XZpinMode(I4, OUTPUT);
    pinMode(encoderpin,INPUT);
    Serial.begin(115200);
}
 
void loop() {
  //setting for one direction
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);
  //  digitalWrite(I3, HIGH);
   // digitalWrite(I4, LOW);
   
 //manipulating enable pin 
    ///////////////////////////analogWrite(E1, 255); // pwm//// it is in void pid controller
//    analogWrite(E2, 255); // Run in full speed 
 
  rpm_measure();
  pidController();
  analogWrite(E1,uDesired); 


}

void rpm_measure(){
  x=0;
while ((millis() - t) < 100){
  
n=digitalRead(encoderpin);

if ( (n==HIGH) && (n0 ==LOW)){
  x++;
}
n0=n;
}
t= millis();

rpm = x * 600 / 32;
//Serial.println(rpm);
}

void pidController(){
  // How long since we last calculated
unsigned long now = millis();
double timeChange = double(now - lastTime);


//Compute all the working error variables
double error = referenceRpm - rpm;
errSum += (error*timeChange);
double dErr = (error-lastErr)/timeChange;

//Compute PID output means uDesired
uDesired = kp * error + ki * errSum + kd* dErr;
//Serial.print("\t");

// remember some variables for next time
lastErr = error;
lastTime = now;


Serial.print(rpm);
Serial.print("\t");
Serial.println(uDesired);
  
  }
