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
#define sensorPin0 A0
#define sensorPin1 A1
#define sensorPin2 A2
#define sensorPin3 A3
#define sensorPin4 A4
#define trigPin0 4
#define trigPin1 5
#define trigPin2 6


void setup() {
  pinMode(trigPin0, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);


  Serial.begin(9600);

  pinMode(echoPin0, INPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
}

void loop() {

  //int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o;
  int a[3][5];
  int b[3][5];


  
    //first 1*5
  digitalWrite(trigPin0, HIGH);
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);

  delay(100);      
  a[0][0]=analogRead(sensorPin0);
  a[0][1]=analogRead(sensorPin1);
  a[0][2]=analogRead(sensorPin2);
  a[0][3]=analogRead(sensorPin3);
  a[0][4]=analogRead(sensorPin4);


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

  delay(100);      
  
   //second 1*5
  digitalWrite(trigPin0, LOW);
  digitalWrite(trigPin1, HIGH);
  digitalWrite(trigPin2, LOW);

  delay(100);    
  a[1][0]=analogRead(sensorPin0);
  a[1][1]=analogRead(sensorPin1);
  a[1][2]=analogRead(sensorPin2);
  a[1][3]=analogRead(sensorPin3);
  a[1][4]=analogRead(sensorPin4);


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

  delay(100);


   //third 1*5
  digitalWrite(trigPin0, LOW);
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, HIGH);
  
  delay(100);    

  a[2][0]=analogRead(sensorPin0);
  a[2][1]=analogRead(sensorPin1);
  a[2][2]=analogRead(sensorPin2);
  a[2][3]=analogRead(sensorPin3);
  a[2][4]=analogRead(sensorPin4);


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
  delay(100); 

  for(int i = 0; i <= 2; i++){
    for(int j = 0; j<= 4; j++){
      if(a[i][j] <= 900){
          a[i][j] = 1;
        }else{
          a[i][j] = 0;
        }
      Serial.println(a[i][j]);
      delay(100);
    }
  }   

  delay(500);

  digitalWrite(trigPin0, HIGH);
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);

  delay(100);      
  b[0][0]=analogRead(sensorPin0);
  b[0][1]=analogRead(sensorPin1);
  b[0][2]=analogRead(sensorPin2);
  b[0][3]=analogRead(sensorPin3);
  b[0][4]=analogRead(sensorPin4);


  Serial.print("TrigPin0High: ");
  Serial.print(b[0][0]);
  Serial.print("-");
  Serial.print(b[0][1]);
  Serial.print("-");
  Serial.print(b[0][2]);
  Serial.print("-");
  Serial.print(b[0][3]);
  Serial.print("-");
  Serial.println(b[0][4]);

  delay(100);      
  
   //second 1*5
  digitalWrite(trigPin0, LOW);
  digitalWrite(trigPin1, HIGH);
  digitalWrite(trigPin2, LOW);

  delay(100);    
  b[1][0]=analogRead(sensorPin0);
  b[1][1]=analogRead(sensorPin1);
  b[1][2]=analogRead(sensorPin2);
  b[1][3]=analogRead(sensorPin3);
  b[1][4]=analogRead(sensorPin4);


  Serial.print("TrigPin1High: ");
  Serial.print(b[1][0]);
  Serial.print("-");
  Serial.print(b[1][1]);
  Serial.print("-");
  Serial.print(b[1][2]);
  Serial.print("-");
  Serial.print(b[1][3]);
  Serial.print("-");
  Serial.println(b[1][4]);

  delay(100);


   //third 1*5
  digitalWrite(trigPin0, LOW);
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, HIGH);
  
  delay(100);    

  b[2][0]=analogRead(sensorPin0);
  b[2][1]=analogRead(sensorPin1);
  b[2][2]=analogRead(sensorPin2);
  b[2][3]=analogRead(sensorPin3);
  b[2][4]=analogRead(sensorPin4);


  Serial.print("TrigPin2High: ");
  Serial.print(b[2][0]);
  Serial.print("-");
  Serial.print(b[2][1]);
  Serial.print("-");
  Serial.print(b[2][2]);
  Serial.print("-");
  Serial.print(b[2][3]);
  Serial.print("-");
  Serial.println(b[2][4]);
  delay(100); 

  for(int i = 0; i <= 2; i++){
    for(int j = 0; j<= 4; j++){
      if(b[i][j] <= 900){
          b[i][j] = 1;
        }else{
          b[i][j] = 0;
        }
      Serial.println(b[i][j]);
      delay(100);
    }
  }   

  int count = 0;

  for(int i = 0; i <= 2; i++){
    for(int j = 0; j<= 4; j++){
      int displacement = a[i][j] - b[i][j];
      if(displacement != 0){
          count++;
        }
      delay(100);
    }
  }   
  Serial.print("Count: ");
  Serial.println(count);
  delay(500);



  int ReadPressureSensor(int matrix[3][5]){
    digitalWrite(trigPin0, HIGH);
    digitalWrite(trigPin1, LOW);
    digitalWrite(trigPin2, LOW);

    delay(100);      
    matrix[0][0]=analogRead(sensorPin0);
    matrix[0][1]=analogRead(sensorPin1);
    matrix[0][2]=analogRead(sensorPin2);
    matrix[0][3]=analogRead(sensorPin3);
    matrix[0][4]=analogRead(sensorPin4);


    Serial.print("TrigPin0High: ");
    Serial.print(matrix[0][0]);
    Serial.print("-");
    Serial.print(matrix[0][1]);
    Serial.print("-");
    Serial.print(matrix[0][2]);
    Serial.print("-");
    Serial.print(matrix[0][3]);
    Serial.print("-");
    Serial.println(matrix[0][4]);

    delay(100);      

     //second 1*5
    digitalWrite(trigPin0, LOW);
    digitalWrite(trigPin1, HIGH);
    digitalWrite(trigPin2, LOW);

    delay(100);    
    matrix[1][0]=analogRead(sensorPin0);
    matrix[1][1]=analogRead(sensorPin1);
    matrix[1][2]=analogRead(sensorPin2);
    matrix[1][3]=analogRead(sensorPin3);
    matrix[1][4]=analogRead(sensorPin4);


    Serial.print("TrigPin1High: ");
    Serial.print(matrix[1][0]);
    Serial.print("-");
    Serial.print(matrix[1][1]);
    Serial.print("-");
    Serial.print(matrix[1][2]);
    Serial.print("-");
    Serial.print(matrix[1][3]);
    Serial.print("-");
    Serial.println(matrix[1][4]);

    delay(100);


     //third 1*5
    digitalWrite(trigPin0, LOW);
    digitalWrite(trigPin1, LOW);
    digitalWrite(trigPin2, HIGH);

    delay(100);    

    matrix[2][0]=analogRead(sensorPin0);
    matrix[2][1]=analogRead(sensorPin1);
    matrix[2][2]=analogRead(sensorPin2);
    matrix[2][3]=analogRead(sensorPin3);
    matrix[2][4]=analogRead(sensorPin4);


    Serial.print("TrigPin2High: ");
    Serial.print(matrix[2][0]);
    Serial.print("-");
    Serial.print(matrix[2][1]);
    Serial.print("-");
    Serial.print(matrix[2][2]);
    Serial.print("-");
    Serial.print(matrix[2][3]);
    Serial.print("-");
    Serial.println(matrix[2][4]);
    delay(100); 

    for(int i = 0; i <= 2; i++){
      for(int j = 0; j<= 4; j++){
        if(matrix[i][j] <= 900){
            matrix[i][j] = 1;
          }else{
            matrix[i][j] = 0;
          }
        Serial.println(matrix[i][j]);
        delay(100);
      }
    }   

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
    digit = 0;
    if (distance <= 86.36){
      digitalWrite(trigPin, LOW);
      Serial.println("Warning"); 
      digit = 1;
    }
    else{
    }
  }
  
  bitcode = 000

  if(count < 4){
    bitSet(bitcode, 0)
  } else {
    bitClear(bitcode,0)
  }

  if(digit = 1){
    bitSet(bitcode, 1)
  } else {
    bitClear(bitcode,1)

}  


