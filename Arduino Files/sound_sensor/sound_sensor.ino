void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

//sound sensor 
//ama_val = analogRead(PIN_ANALOG_IN);
dig_val = digitalRead(PIN_GATE_IN);
//Serial.println(ana_val);
//Serial.print("Detected Voice: ");
//Serial.println(dig_val);

if(dig_val == 1){
  bitSet(states,1); //set the third bit for sound sensor 
}

//delay (20);