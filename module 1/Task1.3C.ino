int sensorState = 0;
int buzzer = 7;  // the pin that the buzzer is atteched to
#define trigPin 2                                   // Pin 12 trigger output
#define echoPin 3                                   // Pin 2 Echo input

int motionState = 0;
int UltraSonicState = 0;

// the time the pulse was sent
volatile long ultrasonic_echo_start = 0;

void setup()
{
  pinMode(trigPin, OUTPUT);                           // Trigger pin set to output
  pinMode(echoPin, INPUT);                            // Echo pin set to input
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);

   
attachInterrupt(digitalPinToInterrupt(12), motion, HIGH);  //Fires motion when sensor rises from 0 to 1
attachInterrupt(digitalPinToInterrupt(echoPin), echo_interrupt, HIGH);  // Attach interrupt to the sensor echo input
}

void loop()
{
 /* if (sensorState == HIGH) {
  digitalWrite(13, HIGH);
  Serial.println("Sensor activated!");
} 
  else {
  digitalWrite(13, LOW);
}*/
 delay(2000);

}

void motion(){
  motionState = HIGH;
  Serial.println("Motion detected!");
  digitalWrite(buzzer, HIGH);
  //noTone(buzzer);     // Stop sound...
  Serial.println("Buzzed!");
}

void echo_interrupt()
{
  Serial.println("UltraSonic Sensor activated!");
    if(UltraSonicState = HIGH){
      digitalWrite(trigPin, HIGH);
    delayMicroseconds(5000);     
    ultrasonic_echo_start = micros(); 
    long distance = (micros() - ultrasonic_echo_start) / 5;
         Serial.println(distance);
         ultrasonic_echo_start = 0;
         digitalWrite(13, HIGH);
         delay(1000);
         digitalWrite(13, LOW); 
         Serial.println("Blinked!");
       digitalWrite(trigPin, LOW);
    }    
 }