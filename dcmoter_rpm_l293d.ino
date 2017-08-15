#define E1 10  // Enable Pin for motor 1
//#define E2 11  // Enable Pin for motor 2
 int encoderpin = 7;
int n;
int n0;
float t=0;
int rpm;
int x=0;
 
#define I1 8  // Control pin 1 for motor 1
#define I2 9  // Control pin 2 for motor 1
//#define I3 12  // Control pin 1 for motor 2
//#define I4 13  // Control pin 2 for motor 2
 
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
    analogWrite(E1, 255); // pwm here
//    analogWrite(E2, 255); // Run in full speed
 
  
 
  rpm_measure();


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
Serial.println(rpm);
}
