# Automatic Irrigation Controller (Arduino) — work in progress

An Arduino-based irrigation controller: a relay switches the water pump/valve on and off, commanded wirelessly over **Bluetooth (HC-05)**. The project is being built incrementally, one tested version at a time.

It builds on an earlier project I developed at university, a classroom automation controller (projectors and air conditioning over IR, Bluetooth commands, RTC scheduling and watchdog), now in its own repository: [Classroom-Controller](https://github.com/guigaf/Classroom-Controller).

## Status

| Version | What it does | Status |
| --- | --- | --- |
| **V1.0 – Bluetooth communication** | Receives characters from a phone/PC over an HC-05 module (`SoftwareSerial`, pins 5/6) and echoes them to the serial monitor | Done |
| **V1.1 – Relay command** | Switches the irrigation relay on pin 2: `a` = on, `b` = off | Done |
| V1.2 – Bluetooth + relay | Control the relay directly from the Bluetooth app | Next |
| V1.3 – Scheduled irrigation | Daily watering schedule with an RTC module | Planned |
| V1.4 – Sensors | Soil-moisture sensor to skip watering when the soil is already wet | Planned |
| V1.5 – Reliability | Watchdog and safe state (pump off) after a reset | Planned |

## Hardware

| Component | Purpose | Pins |
| --- | --- | --- |
| Arduino Uno / Nano | Main controller | — |
| HC-05 Bluetooth module | Wireless commands | RX 5, TX 6 (SoftwareSerial) |
| Relay module (12 V relay + BC337 transistor) | Switches the pump / solenoid valve | 2 |

Wiring diagrams are in [`Placa/`](Placa/) (Fritzing `.fzz` files and PNG/PDF exports).

![Breadboard wiring](Placa/EXEMPLO%20LIAGA%C3%87AO%20PROTOBOARD.png)

## Repository layout

```
Arduino/Codigos/
├── V1.0 - Comunicaçao Bluetooth/    # Bluetooth link
└── V1.1 - Comando por Rele/         # relay control
Placa/                               # schematics and wiring images
```

## Getting started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Open `Arduino/Codigos/V1.1 - Comando por Rele/Comando_Por_Rele/Comando_Por_Rele.ino` and upload it.
3. Open the Serial Monitor at 9600 baud and send `a` (relay on) or `b` (relay off).

No external libraries are needed (`SoftwareSerial` ships with the Arduino IDE).

## Tech

C++ (Arduino) · Bluetooth serial · relay control · Fritzing
