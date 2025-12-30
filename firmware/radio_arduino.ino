#include <TEA5767.h>
#include <TM1637Display.h>
TEA5767 radio = TEA5767();

#define st_up A0
#define st_dwn A1

#define CLK 2
#define DIO 3

TM1637Display display = TM1637Display(CLK, DIO);

float frequency = 87.5; 

void stup() {
  frequency = frequency + 0.1;
  if (frequency > 108.0){
    frequency = 108.0;
  }
  radio.setFrequency(frequency);
  int disp_freq = int(int(frequency*10));
  delay(100);
  display.clear();
  display.showNumberDec(disp_freq, true);

}

void stdwn() {
  frequency = frequency - 0.1;
  if (frequency < 87.5){
    frequency = 87.5;
  }
  radio.setFrequency(frequency);

  int disp_freq = int(int(frequency*10));
  delay(100);
  display.clear();
  display.showNumberDec(disp_freq, true);

}

void setup() {
  pinMode(st_up, INPUT_PULLUP);
  pinMode(st_dwn, INPUT_PULLUP);
  
  radio.setFrequency(frequency);

  display.clear();
  display.setBrightness(7);

}

void loop() {
  if (digitalRead(st_up) == LOW) {stup();}

  if (digitalRead(st_dwn) == LOW) {stdwn();}
  
  delay(200);
}
