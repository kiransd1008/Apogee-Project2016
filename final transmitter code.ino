int D3=7,D2=6,D1=5,D0=4;

int ModuleVcc=;
int sensorPin = A2;

//int waterLevel = 1023;    //zero in water and 1023 in Dry Soil
int waterPercentage=0;    
int sensorVcc = A0;

void setup() {
  Serial.begin(9600);
  pinMode(sensorVcc, OUTPUT);
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorVcc, LOW);
for(int count=0;count<4;count++)
{
  pinMode(count+4,OUTPUT);
  digitalWrite(count+4,LOW);
}
  
}

void loop() {
  for(int count=0;count<4;count++)
     digitalWrite(count+4,LOW);
  digitalWrite(sensorVcc,HIGH);
  
  Serial.println(analogRead(sensorPin));
  
  
  if(analogRead(sensorPin)>1000)
    waterPercentage=4;
  else if(analogRead(sensorPin)>1023*0.75)
    waterPercentage=3;
  else if(analogRead(sensorPin)>1023*0.5)
    waterPercentage=2;
  else if(analogRead(sensorPin)>1023*0.25)
    waterPercentage=1;
  else (analogRead(sensorPin)>0)
    waterPercentage=0;

if(waterPercentage!=0)
{
  for(int count=0;count<waterPercentage;count++)
      digitalWrite(count+4,HIGH);
}      
else 
{
  int i=0;
  while(i<3)
  {
    for(int count=0;count<waterPercentage;count++)
      digitalWrite(count+4,HIGH);
    delay(1000);
    for(int count=0;count<waterPercentage;count++)
      digitalWrite(count+4,LOW);
      i++;
  }
}
  Serial.print("RequiredLevel :");
  Serial.println(requiredLevel);
  digitalWrite(sensorVcc, HIGH);
  Serial.println("sensor : ON");
  waterLevel = analogRead(A2);
  Serial.print("waterLevel : ");
  Serial.println(waterLevel);
  digitalWrite(sensorVcc, LOW);
  Serial.println("sensor: OFF");


  if (waterLevel > requiredLevel) {
    digitalWrite(motorPin, HIGH);
    Serial.println("Motor has started");
  }
  else
    digitalWrite(motorPin, LOW);
  delay(2 * 60 * 1000);
}
