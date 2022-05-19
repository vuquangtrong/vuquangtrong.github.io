#define MIN_BRIGHTNESS    0
#define MAX_BRIGHTNESS    255

#define TIMER_CHANNEL     0
#define TIMER_FREQUENCY   5000
#define TIMER_RESOLUTION  12

int brightness = 0;
int fadeAmount = 5;
int dutyMax = pow(2, TIMER_RESOLUTION) - 1;

void setLedBrightness(uint8_t channel, uint32_t value, uint32_t valueMax = MAX_BRIGHTNESS) {
  uint32_t duty = (dutyMax / valueMax) * min(value, valueMax);
  ledcWrite(channel, duty);
}

void setup() {
  ledcSetup(TIMER_CHANNEL, TIMER_FREQUENCY, TIMER_RESOLUTION);
  ledcAttachPin(LED_BUILTIN, TIMER_CHANNEL);
}

void loop() {
  setLedBrightness(TIMER_CHANNEL, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= MIN_BRIGHTNESS || brightness >= MAX_BRIGHTNESS) {
    fadeAmount = -fadeAmount;
  }
  delay(10);
}
