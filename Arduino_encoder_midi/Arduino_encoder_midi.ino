//Arduino encoder midi - v1.0 by ArtGateOne
#include "MIDIUSB.h"

#define CLK_PIN 2
#define DT_PIN 3
#define SW_PIN 4
#define VCC_PIN 5
#define GND_PIN 6

#define CLK_PIN_2 9
#define DT_PIN_2 10
#define SW_PIN_2 11
#define VCC_PIN_2 12
#define GND_PIN_2 13

#define ENC_NOTE_MINUS 125
#define ENC_NOTE_PLUS 126
#define ENC_2_NOTE_MINUS 123
#define ENC_2_NOTE_PLUS 124



int counter = 64;
int counter_2 = 64;
int click = 0;
int click_2 = 0;
int add = 0;
int add_2 = 0;

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = { 0x09, 0x90 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOn);
}

void encoder_click() {
  delay(1);
  if (digitalRead(SW_PIN) == HIGH) {
    Serial.println("SW ON");
  } else {
    Serial.println("SW ON");
  }
}

void read_encoder() {
  //delay(1);
  if (digitalRead(CLK_PIN) == LOW && digitalRead(DT_PIN) == LOW) {
    click = 1;
  } else if (digitalRead(CLK_PIN) == HIGH && digitalRead(DT_PIN) == LOW && click == 1) {
    add = 1;
  } else if (digitalRead(CLK_PIN) == LOW && digitalRead(DT_PIN) == HIGH && click == 1) {
    add = -1;
  } else if (digitalRead(CLK_PIN) == HIGH && digitalRead(DT_PIN) == HIGH && click == 1) {
    click = 0;
    counter = counter + add;
    send_midi();
  }
}

void read_encoder_2() {
  //delay(1);
  if (digitalRead(CLK_PIN_2) == LOW && digitalRead(DT_PIN_2) == LOW) {
    click_2 = 1;
  } else if (digitalRead(CLK_PIN_2) == HIGH && digitalRead(DT_PIN_2) == LOW && click_2 == 1) {
    add_2 = 1;
  } else if (digitalRead(CLK_PIN_2) == LOW && digitalRead(DT_PIN_2) == HIGH && click_2 == 1) {
    add_2 = -1;
  } else if (digitalRead(CLK_PIN_2) == HIGH && digitalRead(DT_PIN_2) == HIGH && click_2 == 1) {
    click_2 = 0;
    counter_2 = counter_2 + add_2;
    send_midi_2();
  }
}

void send_midi() {
  if (counter > 64) {
    noteOn(0, ENC_NOTE_PLUS, 127);  // Channel, Note, velocity
    MidiUSB.flush();
  } else if (counter < 64) {
    noteOn(0, ENC_NOTE_MINUS, 127);  // Channel, Note, velocity
    MidiUSB.flush();
  }
  counter = 64;
}

void send_midi_2() {
  if (counter_2 > 64) {
    noteOn(0, ENC_2_NOTE_PLUS, 127);  // Channel, Note, velocity
    MidiUSB.flush();
  } else if (counter_2 < 64) {
    noteOn(0, ENC_2_NOTE_MINUS, 127);  // Channel, Note, velocity
    MidiUSB.flush();
  }
  counter_2 = 64;
}

void setup() {
  Serial.begin(9600);

  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(VCC_PIN, OUTPUT);
  pinMode(GND_PIN, OUTPUT);

  digitalWrite(VCC_PIN, HIGH);  // set VCC_PIN HIGH
  digitalWrite(GND_PIN, LOW);   // set GND_PIN LOW

  pinMode(CLK_PIN_2, INPUT);
  pinMode(DT_PIN_2, INPUT);
  pinMode(SW_PIN_2, INPUT_PULLUP);
  pinMode(VCC_PIN_2, OUTPUT);
  pinMode(GND_PIN_2, OUTPUT);

  digitalWrite(VCC_PIN_2, HIGH);  // set VCC_PIN HIGH
  digitalWrite(GND_PIN_2, LOW);   // set GND_PIN LOW
}

void loop() {
  read_encoder();
  read_encoder_2();
}
