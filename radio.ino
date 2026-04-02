#include <TM1637Display.h>

TM1637Display display(2, 3);

// ====== I2C PINS ======
#define SDA A4
#define SCL A5

// ====== BUTTONS ======
#define BTN_UP   A0
#define BTN_DOWN A1

// ====== RADIO WORKING FREQUENCY ======
float frequency = 87.5;   // MHz

// ====== I2C LOW LEVEL ======
void i2c_delay() {
  delayMicroseconds(5);   
}

void i2c_start() {
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);
  digitalWrite(SDA, HIGH);
  digitalWrite(SCL, HIGH);
  i2c_delay();
  digitalWrite(SDA, LOW);
  i2c_delay();
  digitalWrite(SCL, LOW);
}

void i2c_stop() {
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, HIGH);
  i2c_delay();
  digitalWrite(SDA, HIGH);
  i2c_delay();
}

bool i2c_writeByte(uint8_t data) {
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(SDA, (data & 0x80) ? HIGH : LOW);
    data <<= 1;
    i2c_delay();
    digitalWrite(SCL, HIGH);
    i2c_delay();
    digitalWrite(SCL, LOW);
  }

  // ACK
  pinMode(SDA, INPUT_PULLUP);
  digitalWrite(SCL, HIGH);
  i2c_delay();
  bool ack = (digitalRead(SDA) == LOW);
  digitalWrite(SCL, LOW);
  pinMode(SDA, OUTPUT);

  return ack;
}

// ====== TEA5767 CONTROL ======
void tea5767_setFrequency(float freq) {

  
  uint16_t pll = (uint16_t)((4.0 * (freq + 0.225)) / 0.032768);

  uint8_t data[5];

  data[0] = (pll >> 8) & 0x3F;   
  data[1] = pll & 0xFF;          
  data[2] = 0xB0;                
  data[3] = 0x10;                
  data[4] = 0x00;                

  i2c_start();
  i2c_writeByte(0x60 << 1);      // TEA5 address
  for (uint8_t i = 0; i < 5; i++) {
    i2c_writeByte(data[i]);
  }
  i2c_stop();
}


void setup() {
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);

  tea5767_setFrequency(frequency);

  display.setBrightness(7);
  int station = int(frequency*10);
  display.showNumberDec(station, true);
}


void loop() {

  if (digitalRead(BTN_UP) == LOW) {
    frequency += 0.1;
    if (frequency > 108.0) frequency = 108.0;
    tea5767_setFrequency(frequency);
    delay(250);
    int station = int(frequency*10);
    display.showNumberDec(station, true);
  }

  if (digitalRead(BTN_DOWN) == LOW) {
    frequency -= 0.1;
    if (frequency < 87.5) frequency = 87.5;
    tea5767_setFrequency(frequency);
    delay(250);
    int station = int(frequency*10);
    display.showNumberDec(station, true);
  }
}
