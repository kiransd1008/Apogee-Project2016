int D3=7,D2=6,D1=5,D0=4;

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
  digitalWrite(ModuleVcc,);
for(int count=0;count<4;count++)
{
  pinMode(count+4,OUTPUT);
  digitalWrite(count+4,LOW);
}
  
Serial.print("transmitter module is ON");
}

void loop() 
{
      digitalWrite(sensorVcc,HIGH);
      Serial.print("MoistureSensor is on");
      
      Serial.println("SensorReading = ");
      Serial.print(analogRead(sensorPin));
      int sensorReading=analogRead(sensorPin);
      
      digitalWrite(sensorVcc,LOW);
      Serial.print("MoistureSensor is OFF");
      
      if(sensorReading>1023*0.75)
        waterLevel=4;
      else if(sensorReading>1023*0.5)
        waterLevel=3;
      else if(sensorReading>1023*0.25)
        waterLevel=2;
      else
        waterLevel=1;
    
      
    if(waterLevel!=0)
      for(int count=0;count<waterLevel;count++)
          digitalWrite(count+4,HIGH);
}
 delay(5000); 
for(int count=0;count<4;count++)
     digitalWrite(count+4,LOW);

if(waterPercentage!=0)
    delay(2 * 60 * 1000);
}
