int SensorPin1 = 0;
int SensorPin2 = 1;
int SensorPin3 = 2;
int SensorPin4 = 3;
int SensorPin5 = 4;
int SensorPin6 = 5;

int SensorRead1;
int SensorRead2;
int SensorRead3;
int SensorRead4;
int SensorRead5;
int SensorRead6;


void setup() {
  Serial.begin(9600);
 
}

void loop() {
  SensorRead1 = analogRead(SensorPin1);
  SensorRead2 = analogRead(SensorPin2);
  SensorRead3 = analogRead(SensorPin3);
  SensorRead4 = analogRead(SensorPin4);
  SensorRead5 = analogRead(SensorPin5);
  SensorRead6 = analogRead(SensorPin6);

  Serial.print("Sensor1: ");
  Serial.print(SensorRead1);
  Serial.print(" Sensor2: ");
  Serial.print(SensorRead2);
  Serial.print(" Sensor3: ");
  Serial.print(SensorRead3);
  Serial.print(" Sensor4: ");
  Serial.print(SensorRead4);
  Serial.print(" Sensor5: ");
  Serial.print(SensorRead5);
  Serial.print(" Sensor6: ");
  Serial.print(SensorRead6);
  Serial.println();
  if(SensorRead2 < 100 && SensorRead3 < 100 && SensorRead5 < 100 && SensorRead6 < 100 && SensorRead4 < 100 && SensorRead1 < 200){
    Serial.println(" No pressure");
  }
  //heel strike
  else if ( SensorRead2 == 0 && SensorRead3 == 0 && SensorRead5 == 0 && SensorRead6 == 0){
    if ( SensorRead1 > 100 || SensorRead4 > 100){
      Serial.println(" Heel Strike ");
    }
  }
  //heel off
  else if ( SensorRead2 == 0 && SensorRead1 == 0 && SensorRead5 == 0 && SensorRead4 == 0){
    if ( SensorRead3 > 100 || SensorRead6 > 100 || SensorRead5 > 100){
      Serial.println(" Heel Off ");
    }
  }
  //foot flat
  else if ( (SensorRead3 != 0 && SensorRead2 != 0 && SensorRead1 != 0) || (SensorRead4 != 0 && SensorRead5 != 0 && SensorRead6 != 0)){
    Serial.println(" Foot Flat ");
  }

 
  delay(200);
}