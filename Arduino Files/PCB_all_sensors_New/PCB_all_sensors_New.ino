const int trigPin0 = PIN_PB0;
const int echoPin0 = PIN_PB1;
const int trigPin1 = PIN_PB2;
const int echoPin1 = PIN_PB3;
const int trigPin2 = PIN_PB4;
const int echoPin2 = PIN_PB5;
const int trigPin3 = PIN_PD0;
const int echoPin3 = PIN_PD1;
const int PIN_ANALOG_IN = PIN_PC5;
const int PIN_GATE_IN = PIN_PD2;
const int trigPin0_p = PIN_PD5;
const int trigPin1_p = PIN_PD6;
const int trigPin2_p = PIN_PD7;
const int sensorPin0 = PIN_PC0;
const int sensorPin1 = PIN_PC1;
const int sensorPin2 = PIN_PC2;
const int sensorPin3 = PIN_PC3;
const int sensorPin4 = PIN_PC4;

const int BT_RX = PIN_PD3;
const int BT_TX = PIN_PD4;

int BTdelay = 50;
byte newstates = 0b00000000;
unsigned long lasttime = 0;
long duration, distance, Distance0, Distance1, Distance2, Distance3;
int ana_val = 0;
int gate_val = 0;
int n = 0;
int ss_sample_lasttime = 0;
int ss_sample_delay = 400;
int ss_alarm_lasttime = 0;
int ss_alarm_delay = 2000;
int ss_threshold = 150;
bool ss_alarm_remain = false;
bool hasrun = false;
int count = 0;
int ps_delay=10;
int ps_threshold = 1018;
unsigned long last_ps_time = 0;
int displacement = 0;
int dig_val[4] = {0,0,0,0};


int a[3][5] = {0};
int b[3][5] = {0};


#include <SoftwareSerial.h>
SoftwareSerial hc05(BT_TX, BT_RX);

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin0, OUTPUT);
  pinMode(echoPin0, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(PIN_ANALOG_IN, INPUT);
  pinMode(trigPin0_p, OUTPUT);
  pinMode(trigPin1_p, OUTPUT);
  pinMode(trigPin2_p, OUTPUT);
  hc05.begin(9600);
}

void loop() {
  byte states = 0b00000000;
  //Ultrasonic Sensor
  SonarSensor(trigPin0, echoPin0); //need 65
  Distance0 = distance;
  SonarSensor(trigPin1, echoPin1);  //need 65
  Distance1 = distance;
  SonarSensor(trigPin2, echoPin2);
  Distance2 = distance;  
  SonarSensor(trigPin3, echoPin3);
  Distance3 = distance;

  int arr[4] = {Distance0, Distance1, Distance2, Distance3};
  // int arr[1] = {Distance1};
  //int arr[2] = {Distance1, Distance3};
  //int arr[3] = {Distance0, Distance1, Distance3};

  for(int i = 0; i <= 3; i++){
    if(arr[i] <= 65){
      bitSet(states, 0);//set the 1st bit
      break;
    }
  }

  //Sound Sensor
  //analog version
  // ana_val = analogRead(PIN_ANALOG_IN);

  // if(ana_val >= 150){
  //   bitSet(states, 1);//set the 2nd bit
  // }
  gate_val = digitalRead(PIN_GATE_IN);
  if(gate_val == 1){
    bitSet(states, 1);//set the 2nd bit
  }
  //-------------------------------------------------------------------
  // timed version
  // if(dig_val[0] == 1 && dig_val[1] == 1 && dig_val[2] == 1 && dig_val[3] == 1){
  //   bitSet(states, 1);
  //   //ss_alarm_remain = true;
  //   ss_alarm_lasttime = millis();
  // }

  // if(millis() >= ss_sample_lasttime + ss_sample_delay){
  //   for (int i = 0; i < 3; ++i) {
  //     dig_val[i] = dig_val[i + 1];
  //   }
  //   dig_val[3] = digitalRead(PIN_GATE_IN);
  //   ss_sample_lasttime = millis();
  //   // n++;
  // }
  //-------------------------------------------------------------------

  // //  else {
  // //   ss_alarm_remain = false;
  // // }

  // if(n == 4){
  //   n = 0;
  // }  

  // if(millis() <= ss_alarm_lasttime + ss_alarm_delay){
  //   if (ss_alarm_remain == true) {
  //     bitSet(states, 1);
  //   }
  // }
  
  //Pressure Sensor
  if(hasrun == false){
    ReadPressureSensor();
    for(int i = 0; i <= 2; i++){
      for(int j = 0; j<= 4; j++){
        if(a[i][j] <= ps_threshold){
          a[i][j] = 1;
        }else{
          a[i][j] = 0;
        }
        b[i][j] = a[i][j];
        a[i][j] = 0;
      }
    }

    hasrun = true;  
  }

  for(int i = 0; i <= 9; i++){
    ReadPressureSensor(); 
  }  

for(int i = 0; i <= 2; i++){
    for(int j = 0; j<= 4; j++){
      a[i][j] = a[i][j] / 10;
      if(a[i][j] <= ps_threshold){
          a[i][j] = 1;
        }else{
          a[i][j] = 0;
        }
      //calculate the number of position change
      displacement = a[i][j]-b[i][j];
      if(displacement != 0){
        count++;
      }
    }
  }  

  if(count >= 1){
    bitSet(states, 2);
  }

  displacement = 0;
  count = 0;
  for(int i = 0; i <= 2; i++){
    for(int j = 0; j <= 4; j++){
      b[i][j] = a[i][j];
      a[i][j] = 0;
    }
  }

  if(millis() < lasttime + BTdelay){
    newstates = newstates | states;
  } else {
    hc05.write(newstates);
    newstates = newstates & 0;
    lasttime = millis();
  }
}

void SonarSensor(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
}
void ReadPressureSensor(){
  digitalWrite(trigPin0_p, HIGH);
  digitalWrite(trigPin1_p, LOW);
  digitalWrite(trigPin2_p, LOW);
  
  delayMicroseconds(ps_delay);      
  a[0][0]=a[0][0]+analogRead(sensorPin0);
  a[0][1]=a[0][1]+analogRead(sensorPin1);
  a[0][2]=a[0][2]+analogRead(sensorPin2);
  a[0][3]=a[0][3]+analogRead(sensorPin3);
  a[0][4]=a[0][4]+analogRead(sensorPin4);


  //second 1*5
  digitalWrite(trigPin0_p, LOW);
  digitalWrite(trigPin1_p, HIGH);
  digitalWrite(trigPin2_p, LOW);

  delayMicroseconds(ps_delay);    
  a[1][0]=a[1][0]+analogRead(sensorPin0);
  a[1][1]=a[1][1]+analogRead(sensorPin1);
  a[1][2]=a[1][2]+analogRead(sensorPin2);
  a[1][3]=a[1][3]+analogRead(sensorPin3);
  a[1][4]=a[1][4]+analogRead(sensorPin4);

  //third 1*5
  digitalWrite(trigPin0_p, LOW);
  digitalWrite(trigPin1_p, LOW);
  digitalWrite(trigPin2_p, HIGH);
  
  delayMicroseconds(ps_delay);    
  
  a[2][0]=a[2][0]+analogRead(sensorPin0);
  a[2][1]=a[2][1]+analogRead(sensorPin1);
  a[2][2]=a[2][2]+analogRead(sensorPin2);
  a[2][3]=a[2][3]+analogRead(sensorPin3);
  a[2][4]=a[2][4]+analogRead(sensorPin4);

}