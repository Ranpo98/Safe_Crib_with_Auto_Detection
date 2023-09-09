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

#define trigPin0 4
#define trigPin1 5
#define trigPin2 6
#define trigPin3 7
#define trigPin4 8

void setup() {
  pinMode(trigPin0, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(trigPin4, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  //first 1*3
  digitalWrite(trigPin0, HIGH);
  digitalWrite(trigPin1, LOW);

  delay(20);      
  int a=analogRead(sensorPin0);
  int b=analogRead(sensorPin1);
  int c=analogRead(sensorPin2);

  Serial.print("TrigPin0High: ");
  Serial.print(a);
  Serial.print("-");
  Serial.print(b);
  Serial.print("-");
  Serial.println(c);

  delay(20);      
  
   //second 1*3
  digitalWrite(trigPin1, HIGH);
  digitalWrite(trigPin2, LOW);

  delay(1000);    
  int d =analogRead(sensorPin0);   
  int e =analogRead(sensorPin1);
  int f =analogRead(sensorPin2);
  Serial.print("TrigPin0Low: ");
  Serial.print(d);
  Serial.print("-");
  Serial.print(e);
  Serial.print("-");
  Serial.println(f);

  delay(20);

  //third 1*3
  digitalWrite(trigPin2, HIGH);
  digitalWrite(trigPin3, LOW);

  delay(1000);    
  int g =analogRead(sensorPin0);   
  int h =analogRead(sensorPin1);
  int i =analogRead(sensorPin2);
  Serial.print("TrigPin0Low: ");
  Serial.print(g);
  Serial.print("-");
  Serial.print(h);
  Serial.print("-");
  Serial.println(i);

  delay(20);

  //fourth 1*3     
  digitalWrite(trigPin3, HIGH);
  digitalWrite(trigPin4, LOW);
  delay(1000);    
  int j =analogRead(sensorPin0);   
  int k =analogRead(sensorPin1);
  int l =analogRead(sensorPin2);
  Serial.print("TrigPin0Low: ");
  Serial.print(j);
  Serial.print("-");
  Serial.print(k);
  Serial.print("-");
  Serial.println(l);

  delay(20);

  //fifth 1*3
  digitalWrite(trigPin4, LOW);
  digitalWrite(trigPin0, HIGH);
  delay(1000);    
  int m =analogRead(sensorPin0);   
  int n =analogRead(sensorPin1);
  int o =analogRead(sensorPin2);
  Serial.print("TrigPin0Low: ");
  Serial.print(m);
  Serial.print("-");
  Serial.print(n);
  Serial.print("-");
  Serial.println(o);

  delay(20);
}