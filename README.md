# 🎛️ AetherTone – Air Gesture MIDI Controller

AetherTone is a unique USB MIDI controller that lets you **control music using hand gestures in the air**.
Instead of a traditional keyboard, this instrument uses an ultrasonic sensor, buttons, and a potentiometer
to create expressive music.

Built for **Hack Club** 🚀

---

## ✨ Features
- ✋ Hand movement controls **pitch bend**
- 🎹 Buttons trigger MIDI notes
- 🎚️ Knob controls note velocity
- 🎵 Works with any DAW (FL Studio, Ableton, GarageBand, etc.)
- 🔌 Plug-and-play USB MIDI

---

## 🧠 How It Works
- An **HC-SR04 ultrasonic sensor** measures hand distance
- Distance is mapped to **MIDI Pitch Bend**
- Buttons send **Note On / Note Off**
- A potentiometer adjusts **velocity (intensity)**

This creates a futuristic, expressive instrument you can play without touching keys.

---

## 🧰 Hardware Required
- Arduino Leonardo / Pro Micro / RP2040
- HC-SR04 Ultrasonic Sensor
- 4 Push Buttons
- 1 Potentiometer
- Jumper wires
- Breadboard

---

## 🎹 MIDI Mapping

| Input | MIDI Action |
|------|------------|
Buttons | C, D, E, G notes |
Potentiometer | Velocity |
Hand Distance | Pitch Bend |

---

## 📂 File Structure
