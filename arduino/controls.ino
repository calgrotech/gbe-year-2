/*

*/
# define HIGH_TEMP (18.3333)
# define LOW_TEMP (15.5556)
# define MIN_FAN_SPEED (0.8)
# define MAX_FAN_SPEED (1.0)


void setup() {
    
}

/**
 * Returns fan speed in range [MIN_FAN_SPEED, MAX_FAN_SPEED].
 */
float fan_speed(float curr_temp) {
  float speed = ((MAX_FAN_SPEED - MIN_FAN_SPEED) / (HIGH_TEMP - LOW_TEMP)) * (curr_temp - HIGH_TEMP) + MAX_FAN_SPEED;
  return constrain(speed, MIN_FAN_SPEED, MAX_FAN_SPEED);
}

void loop() {
    
}

