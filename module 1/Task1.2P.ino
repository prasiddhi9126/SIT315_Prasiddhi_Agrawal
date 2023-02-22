int sensorState = 0;
int buzzer = 7;  // the pin that the buzzer is atteched to

void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(2), motion, RISING);  //Fires motion when sensor rises from 0 to 1
}

void loop()
{
  if (sensorState == HIGH) {
  digitalWrite(13, HIGH);
  Serial.println("Sensor activated!");
} 
  else {
  digitalWrite(13, LOW);
}

}

void motion(){
  Serial.println("Motion detected!");
  digitalWrite(buzzer, HIGH);
  //noTone(buzzer);     // Stop sound...
  Serial.println("Buzzed!");
}