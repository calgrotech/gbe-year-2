
# define HIGH_TEMP (18.3333)
# define LOW_TEMP (15.5556)
# define MIN_FAN_SPEED (0.8)
# define MAX_FAN_SPEED (1.0)

int ThermistorPin = 0;
int motorPin = 3;
int ledPin = 13;
int period = 1000; // Sample period

/*
 * Thermistor constants
 * Resistor values used to calculate temperature from the voltage divider
 */
float R1 = 10000;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  delay(period);
  float curr_temp = getTemperature(ThermistorPin, R1);

  Serial.print("Temperature: "); 
  Serial.print(curr_temp);
  Serial.println(" C"); 

  setFanFromTemp(curr_temp, motorPin);
}

/*
 * Sets the fan speed based on the desired temperature
 */
void setFanFromTemp(float temp, int pin) {
  float fs = fan_speed(temp);
  int ms = (int) (fs * 255); // Multiply by 255 for now for motor control
  if (ms > 0) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
  analogWrite(pin, fs);
}

/**
 * Returns fan speed in range [MIN_FAN_SPEED, MAX_FAN_SPEED].
 */
float fan_speed(float curr_temp) {
  float speed = ((MAX_FAN_SPEED - MIN_FAN_SPEED) / (HIGH_TEMP - LOW_TEMP)) * (curr_temp - HIGH_TEMP) + MAX_FAN_SPEED;
  return constrain(speed, MIN_FAN_SPEED, MAX_FAN_SPEED);
}

/*
 * Returns the temperature given by one thermistor at pin thermPin
 */
float getTemperature(int thermPin, float R1) {
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; // Thermal constants
  int V0 = analogRead(thermPin); // Returns a value between 0 and 1023
  float R2 = R1 * (1023.0 / (float) V0 - 1.0);
  float logR2 = log(R2);
  float T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // Temperature in Kelvin
  return T - 273.15; // Temperature in Celsius
  T = (T * 9.0)/ 5.0 + 32.0; // Temperature in Farenheit
}
