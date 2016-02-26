int sensorPin = A2;
int motorPin = 12;
int requiredLevel = 0;
int waterLevel = 1023;    //zero in water and 1023 in Dry Soil
int pushButton = A5;
int sensorVcc = A0;
int buttonState;

void setup() {
  Serial.begin(9600);
  pinMode(sensorVcc, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(pushButton, INPUT);
  for (int i = 2; i < 12; i++)
    pinMode(i, OUTPUT);
  digitalWrite(sensorVcc, LOW);

  int count = 0;
  delay(2000);
  buttonState = analogRead(pushButton);

  delay(1000);
  int p = 1;
  while (p)
  {
    p = 0;
    delay(500);
    buttonState = analogRead(pushButton);
    if (buttonState > 1000)
    {
      for (int i = 2; i < 12; i++)
      {
        digitalWrite(i, HIGH);
        delay(500);
        requiredLevel = 1000 - (100 * (i - 1));
        if (analogRead(pushButton) < 1000)
        {
          break;
          delay(2000);
        }
      }
    }
  }
  delay(5000);
  for (int i = 2; i < 12; i++)
    digitalWrite(i, LOW);
}

void loop() {
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
