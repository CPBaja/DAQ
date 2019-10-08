const int maxSize = 1000;

const int sensorPin = A0;    // select the input pin for the potentiometer
int sensorReadings[maxSize];
unsigned long timestampReadings[maxSize];
int headIndex = 0;
unsigned long startTime;
unsigned long resultTime;

void setup()
{
  Serial.begin(9600);
  startTime = micros();
}

void loop()
{
  if(headIndex >= maxSize)
  {
    resultTime = micros() - startTime;
    /*Serial.print(maxSize);
    Serial.print(" values read and saved in ");
    Serial.print(resultTime);
    Serial.println(" microseconds.");*/
    headIndex = 0;
    startTime = micros();
    for(int i = 0; i < maxSize; i++)
    {
      Serial.print(sensorReadings[i]);
      Serial.print(",");
    }
    Serial.println();
  }

  sensorReadings[headIndex] = analogRead(sensorPin);
  timestampReadings[headIndex] = micros();
  headIndex++;
}
