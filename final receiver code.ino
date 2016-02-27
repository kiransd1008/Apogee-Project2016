//int D0=4,D1=5,D2=6,D3=7;
int RxModuleVcc=9;
int motorPin = 12;
//int waterLevel = 1023;    //zero in water and 1023 in Dry Soil
int ReceivingSignal=8;
int PushButton=A5;
int ReferenceLevel=0;
int Signal=0;
void setup() {
  Serial.begin(9600);
  pinMode(RxModuleVcc,OUTPUT);
  digitalWrite(RxModuleVcc,LOW);
  
  pinMode(ReceivingSignal, INPUT);
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin,LOW);
  for (int i = 4; i < 8; i++)
    {
      pinMode(i, OUTPUT);
      digitalWrite(i,LOW);
    }
  Serial.println("set reference level");
  Serial.println("push the push button for changing the waterlevel by 25 percent");
  Serial.println("Tap the push button for continuously 3 seconds to save the Reference Waterlevel");
   while(analogRead(PushButton)<600);
   //setReferenceWaterLevel();
   ReferenceLevel = setReferenceWaterLevel();
    Serial.print("reference Level is ");  
    Serial.println(ReferenceLevel);
  for (int i = 4; i < 8; i++)
    {
      digitalWrite(i,LOW);
    }
  for (int i = 4; i < 8; i++)
      pinMode(i, INPUT);
  //while(ReceivingSignal()==0);
  
  
}

void loop() {
  digitalWrite(RxModuleVcc, HIGH);
  Serial.println("RxModule is turned ON");
  Signal=ReadSignal();
  Serial.println(Signal);
  display(Signal);
  digitalWrite(RxModuleVcc,LOW);
  Serial.println("RxModule is turned OFF");

  if (Signal < ReferenceLevel) {
    digitalWrite(motorPin, HIGH);
    Serial.println("Motor has started");
  }
  else
    digitalWrite(motorPin, LOW);
  delay(2 * 60 * 1000);
}

void display(int leds){
  leds=leds%5;
  for(int count=0;count+4<8;count++){
    digitalWrite(count+4,LOW);
  }
  for(int count=0;count<leds;count++){
    digitalWrite(count+4,HIGH);
  }
  return;
}
int ReadSignal(){
  while(digitalRead(ReceivingSignal)==0);
  int level=0;
  for(int i=0;i<4;i++)
    level+=digitalRead(i+4);
  return level;
}
int setReferenceWaterLevel(){
  int counter=0,count1=0,ButtonState=0,LastButtonState=0;
  while(count1<=6)
    {
        if(analogRead(PushButton)>650)
        ButtonState=HIGH;
        else
        ButtonState=LOW;
      if(LastButtonState!=ButtonState)
        {
          delay(50);
          if(analogRead(PushButton)>=650)
          {
            count1=0;
            counter++;
            display(counter);
            delay(400);
          }
        }
      else if(ButtonState==HIGH)
        {
          count1++;
          delay(500);
        }
      LastButtonState=ButtonState;
    }
    //display(counter);
    //delay(500);
    display(0);
    delay(1000);
    display(counter);
    delay(1000);
    display(0);
     counter=counter%5;
 return counter;   
}
