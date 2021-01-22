int ThermistorPin = 0;
int motorPin = 3;
int ledPin = 13;

int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" F"); 

  delay(500);

  if (T > motorThresh) {
    digitalWrite(ledPin, HIGH);
    analogWrite(motorPin, 100);
  }

  delay(1000);'
  analogWrite(motorPin, 0);
  digitalWrite(ledPin, HIGH);

}
