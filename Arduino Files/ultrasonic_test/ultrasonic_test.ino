const int trigPin0 = 8;
const int echoPin0 = 2;
const int trigPin1 = 12;
const int echoPin1 = 4;
const int trigPin2 = 13;
const int echoPin2 = 7;

long duration, distance, Distance0, Distance1, Distance2;

void setup() {
pinMode(trigPin0, OUTPUT);
pinMode(echoPin0, INPUT);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
Serial.begin(9600);
}
void loop() {
  //multiple ultrasonic sensors
  SonarSensor(trigPin0, echoPin0);
  Distance0 = distance;
  SonarSensor(trigPin1, echoPin1);
  Distance1 = distance;
  SonarSensor(trigPin2, echoPin2);
  Distance2 = distance;  
  Serial.print(Distance0);
  Serial.print(" - ");
  Serial.print(Distance1);
  Serial.print(" - ");
  Serial.println(Distance2);
}
void SonarSensor(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if (distance <= 86.36){
    digitalWrite(trigPin, LOW);
    Serial.println("Warning"); 
  }
  else{
  }
}
