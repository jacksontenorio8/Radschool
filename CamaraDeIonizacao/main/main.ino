const int botaoPin = 14;  
const int circuitoPin = 27; 

void setup() {
  
  pinMode(botaoPin, INPUT_PULLUP);
  
  
  pinMode(circuitoPin, OUTPUT);


  digitalWrite(circuitoPin, LOW);
}

void loop() {
  
  int estadoBotao = digitalRead(botaoPin);
  
  
  if (estadoBotao == LOW) {
    digitalWrite(circuitoPin, HIGH); 
  } else {
    digitalWrite(circuitoPin, LOW); 
  }
  
  
  delay(50);
}

