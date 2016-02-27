//D3=7,D2=6,D1=5,D0=4;

int ModuleVcc=A5;
int sensorPin = A2;

//int waterLevel = 1023;    //zero in water and 1023 in Dry Soil
int waterLevel=0;    
int sensorVcc = A0;

void setup() {
  Serial.begin(9600);
  pinMode(sensorVcc, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(ModuleVcc, OUTPUT);
  digitalWrite(sensorVcc, LOW);
  digitalWrite(ModuleVcc,LOW);
for(int count=0;count<4;count++)
{
  pinMode(count+4,OUTPUT);
  digitalWrite(count+4,LOW);
}
  
Serial.println("transmitter module is ON");
}

void loop() 
{
      digitalWrite(sensorVcc,HIGH);
      Serial.println("MoistureSensor is on");
      
      Serial.print("SensorReading =  ");
      int sensorReading=analogRead(sensorPin);
      Serial.println(sensorReading);
      digitalWrite(sensorVcc,LOW);
      Serial.println("MoistureSensor is OFF");
      digitalWrite(ModuleVcc,HIGH);
      if(sensorReading>350)
        waterLevel=0;
      else if(sensorReading>1023*0.75*0.36)
        waterLevel=1;
      else if(sensorReading>1023*0.18)
        waterLevel=2;
      else if(sensorReading>1023*0.25*0.36)
        waterLevel=3;
      else
        waterLevel=4;
    Serial.print("waterLevel  ");
    Serial.println(waterLevel);
      Serial.println(" ");
    Serial.println(" ");
    if(waterLevel!=0)
      for(int count=0;count<waterLevel;count++)
          digitalWrite(count+4,HIGH);
     else
     for(int count=0;count<4;count++)
          digitalWrite(count+4,LOW);

    delay(60*1000);    //delay for one minute
}
