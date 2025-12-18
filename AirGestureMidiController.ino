/*
  Air-Gesture MIDI Controller
  Unique Hack Club Project
  Author: Ars 😎
*/

#include <MIDIUSB.h>

// ========== PINS ==========
#define TRIG_PIN 3
#define ECHO_PIN 2

int notePins[4] = {4, 5, 6, 7};
byte notes[4] = {60, 62, 64, 67}; // C D E G

#define POT_PIN A0

// ========== STATES ==========
bool noteState[4] = {false, false, false, false};

// ========== FUNCTIONS ==========
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  return duration / 58;
}

void sendNoteOn(byte note, byte velocity) {
  midiEventPacket_t event = {0x09, 0x90, note, velocity};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}

void sendNoteOff(byte note) {
  midiEventPacket_t event = {0x08, 0x80, note, 0};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}

void sendPitchBend(int value) {
  value = constrain(value, -8192, 8191);
  byte lsb = (value + 8192) & 0x7F;
  byte msb = (value + 8192) >> 7;
  midiEventPacket_t event = {0x0E, 0xE0, lsb, msb};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}

// ========== SETUP ==========
void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(notePins[i], INPUT_PULLUP);
  }
}

// ========== LOOP ==========
void loop() {
  // 🎚 Velocity Control
  int potVal = analogRead(POT_PIN);
  byte velocity = map(potVal, 0, 1023, 20, 127);

  // 🎵 Note Buttons
  for (int i = 0; i < 4; i++) {
    bool pressed = !digitalRead(notePins[i]);
    if (pressed && !noteState[i]) {
      sendNoteOn(notes[i], velocity);
      noteState[i] = true;
    }
    if (!pressed && noteState[i]) {
      sendNoteOff(notes[i]);
      noteState[i] = false;
    }
  }

  // ✋ Air Pitch Control
  long distance = getDistance();
  if (distance > 5 && distance < 40) {
    int pitch = map(distance, 5, 40, -8192, 8191);
    sendPitchBend(pitch);
  }

  delay(10);
}
