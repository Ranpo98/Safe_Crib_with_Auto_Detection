/***************************************************
* Piezo Vibration Sensor 
* ****************************************************
* This example The sensors detect vibration

* @author linfeng(490289303@qq.com)
* @version  V1.0
* @date  2016-2-26

* GNU Lesser General Public License.
* See <http://www.gnu.org/licenses/> for details.
* All above must be included in any redistribution
* ****************************************************/
const int trigPin0 = 7;
const int echoPin0 = 8;
const int trigPin1 = 9;
const int echoPin1 = 10;
const int trigPin2 = 11;
const int echoPin2 = 12;
//const int trigPin3 = 0;
//const int echoPin3 = 1;

//long duration, distance, Distance0, Distance1, Distance2, Distance3;
long duration, distance, Distance0, Distance1, Distance2;

#define sensorPin0 A0
#define sensorPin1 A1
#define sensorPin2 A2
#define sensorPin3 A3
#define sensorPin4 A4
#define PIN_ANALOG_IN A5
#define trigPin0_p 4
#define trigPin1_p 5
#define trigPin2_p 6
#define PIN_GATE_IN 13

int a[3][5] = {0};
int b[3][5];
int count = 0;
int displacement = 0;
bool hasrun = false;
int dig_val, ana_val;
int ps_delay=10;
int ps_threshold = 1000;
byte test = 0b01000001;

int BTdelay = 100;
byte newstates = 0b00000000;
unsigned long lasttime = 0;

#include <SoftwareSerial.h>
SoftwareSerial hc05(3,2);


void setup() {
  pinMode(trigPin0, OUTPUT);
  pinMode(echoPin0, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  //pinMode(trigPin3, OUTPUT);
  //pinMode(echoPin3, INPUT);
  pinMode(trigPin0_p, OUTPUT);
  pinMode(trigPin1_p, OUTPUT);
  pinMode(trigPin2_p, OUTPUT);
  pinMode(PIN_GATE_IN, INPUT);


  Serial.begin(9600);
  hc05.begin(9600);
  //Serial.println("Initialized");
  //delay(210);   //due to the fact that the sound sensor need some time to setup, otherwise it will output a digital 1 through gate output

}

void loop() {


  byte states = 0b00000000;

  //multiple ultrasonic sensors
  SonarSensor(trigPin0, echoPin0);
  Distance0 = distance;
  SonarSensor(trigPin1, echoPin1);
  Distance1 = distance;
  SonarSensor(trigPin2, echoPin2);
  Distance2 = distance;  
  //SonarSensor(trigPin3, echoPin3);
  //Distance3 = distance;  
  
  /*
  Serial.print(Distance0);
  Serial.print(" - ");
  Serial.print(Distance1);
  Serial.print(" - ");
  Serial.print(Distance2);
  Serial.print(" - ");
  Serial.println(Distance3);
  delay(20);
  */
  
  //int arr[4] = {Distance0, Distance1, Distance2, Distance3};
  int arr[3] = {Distance0, Distance1, Distance2};

  for(int i = 0; i <= 2; i++){
    if(arr[i] <= 50){
      bitSet(states, 0);//set the 1st bit
      //delay(100);
      //Serial.println(states);
      //delay(100);
      break;
    }
  }


  //sound sensor
  ana_val = analogRead(PIN_ANALOG_IN);
  //dig_val = digitalRead(PIN_GATE_IN);
  //Serial.println(ana_val);
  //Serial.print("Detected Voice: ");
  //Serial.println(dig_val);

  if(ana_val >= 300){
    bitSet(states, 1);//set the 2nd bit
  }

  //delay(10);





  //pressure sensor------------------------------------------------------------------------------------
  //initialize the measurement from the pressure sensor and digitalize the matrix
  if(hasrun == false){
    //Serial.print("HasRun is ");
    //Serial.println(hasrun);
    ReadPressureSensor();
    for(int i = 0; i <= 2; i++){
      for(int j = 0; j<= 4; j++){
        if(a[i][j] <= ps_threshold){
          a[i][j] = 1;
        }else{
          a[i][j] = 0;
        }
        //Serial.println(a[i][j]);
        //delay(200);
      }

    }

    hasrun = true;  
    //Serial.print("HasRun is ");
    //Serial.println(hasrun);
  }
  
  //copying the previous reading to matrix b
  for(int i = 0; i <= 2; i++){
    for(int j = 0; j <= 4; j++){
      b[i][j] = a[i][j];
    }
  }

  //get the newest measurement
  ReadPressureSensor();
  //digitalize the newest measurement
  for(int i = 0; i <= 2; i++){
    for(int j = 0; j<= 4; j++){
      if(a[i][j] <= ps_threshold){
          a[i][j] = 1;
        }else{
          a[i][j] = 0;
        }
      //Serial.println(a[i][j]);
      //delay(200);
      //calculate the number of position change
      displacement = a[i][j]-b[i][j];
      if(displacement != 0){
        count++;
      }
    }
  }  

  //Serial.print("Count is ");
  //Serial.println(count);

  //set the 3rd bit
  if(count >= 1){
    bitSet(states, 2);
  }

  displacement = 0;
  count = 0;
 
  //states += 48;

  //Serial.print("Byte is: ");
  //Serial.println(states);
  //delay(100);
  //hc05.write(states);
  //delay(1000);
/*  
  if (test + 1 > 90) {
    test = 65;
  } else {
    test = test + 1;
  }
  //delay(10);
*/
  if(millis() < lasttime + BTdelay){
    newstates = newstates | states;
  } else {
    hc05.write(newstates);
    newstates = newstates & 0;
    lasttime = millis();
    //Serial.println(newstates);
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
  a[0][0]=analogRead(sensorPin0);
  a[0][1]=analogRead(sensorPin1);
  a[0][2]=analogRead(sensorPin2);
  a[0][3]=analogRead(sensorPin3);
  a[0][4]=analogRead(sensorPin4);

  /*
  Serial.print("TrigPin0High: ");
  Serial.print(a[0][0]);
  Serial.print("-");
  Serial.print(a[0][1]);
  Serial.print("-");
  Serial.print(a[0][2]);
  Serial.print("-");
  Serial.print(a[0][3]);
  Serial.print("-");
  Serial.println(a[0][4]);
  */

  delayMicroseconds(ps_delay);      

  //second 1*5
  digitalWrite(trigPin0_p, LOW);
  digitalWrite(trigPin1_p, HIGH);
  digitalWrite(trigPin2_p, LOW);

  delayMicroseconds(ps_delay);    
  a[1][0]=analogRead(sensorPin0);
  a[1][1]=analogRead(sensorPin1);
  a[1][2]=analogRead(sensorPin2);
  a[1][3]=analogRead(sensorPin3);
  a[1][4]=analogRead(sensorPin4);

  /*
  Serial.print("TrigPin1High: ");
  Serial.print(a[1][0]);
  Serial.print("-");
  Serial.print(a[1][1]);
  Serial.print("-");
  Serial.print(a[1][2]);
  Serial.print("-");
  Serial.print(a[1][3]);
  Serial.print("-");
  Serial.println(a[1][4]);
  */

  delayMicroseconds(ps_delay);

  //third 1*5
  digitalWrite(trigPin0_p, LOW);
  digitalWrite(trigPin1_p, LOW);
  digitalWrite(trigPin2_p, HIGH);
  
  delayMicroseconds(ps_delay);    

  a[2][0]=analogRead(sensorPin0);
  a[2][1]=analogRead(sensorPin1);
  a[2][2]=analogRead(sensorPin2);
  a[2][3]=analogRead(sensorPin3);
  a[2][4]=analogRead(sensorPin4);

  /*
  Serial.print("TrigPin2High: ");
  Serial.print(a[2][0]);
  Serial.print("-");
  Serial.print(a[2][1]);
  Serial.print("-");
  Serial.print(a[2][2]);
  Serial.print("-");
  Serial.print(a[2][3]);
  Serial.print("-");
  Serial.println(a[2][4]);
  */
  delayMicroseconds(ps_delay); 

}
