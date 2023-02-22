const uint8_t LedPin1 = 8;
const uint8_t LedPin2 = 9;
const uint8_t PIR1 = 2;
const uint8_t PIR2 = 3;
const uint8_t PIR3 = 4;
const int buzzer = 7;
const byte TimerLed = 13;

uint8_t PIR1State, PIR2State, PIR3State = 0;

void setup()
{
    Serial.begin(9600);  //initialize serial

    pinMode(TimerLed, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(LedPin1, OUTPUT);
    pinMode(LedPin2, OUTPUT);
    pinMode(PIR1, INPUT);
    pinMode(PIR2, INPUT);
    pinMode(PIR3, INPUT);
    PCICR |= 0b00000100; // turn on port d
    PCMSK2 |= 0b00011100; // enable pins 2, 3, and 4

    startTimer(); //0.5 Hz = 2 seconds per interupt
}

void loop()
{
  digitalWrite(LedPin1, PIR1State);
    digitalWrite(LedPin2, PIR2State);
    digitalWrite(buzzer, PIR3State);
}

void startTimer(){
  noInterrupts();
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  // led 13 to blink every 2 seconds using:
  // http://www.8bit-era.cz/arduino-timer-interrupts-calculator.html
  
  // x = 16 Mhz / (prescaler * x) - 1, x in Hz
  // => 16 Mhz / x(x+1) = prescalar
  
  OCR1A = 31249; // 0.5Hz = 16000000 / (1024 * 0.5) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  interrupts();
}

// timer interupt
ISR(TIMER1_COMPA_vect){
   digitalWrite(TimerLed, digitalRead(TimerLed) ^ 1);
}

//Port D interupt
ISR(PCINT2_vect) // Port D, PCINT16 - PCINT23
{
    PIR1State = PIND & B00000100;
    PIR2State = PIND & B00001000;
    PIR3State = PIND & B00010000;
    if (PIR1State)
    {
        Serial.println("PIR1 State Change");
        Serial.println("LED 1 Blinked!!!"); 
    }
    if (PIR2State)
    {
        Serial.println("PIR2 State Change");
        Serial.println("LED 2 Blinked!!!");
    }
    if (PIR3State)
    {
        Serial.println("PIR3 State Change");
        Serial.println("Buzzer Buzzed!!!");
    }
    
}