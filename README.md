# Smart Sensor Hub with 8-bit Shift Registers

This project uses an Arduino Uno, an ultrasonic distance sensor (HC-SR04), and a 74HC595 8-bit shift register to visually display measured distances on 8 LEDs [project photos](https://github.com/KelennaUdo/Ultrasonic-sensor-and-8-bit-register/blob/Master/project%20photos.pdf)
.

## Features

- Measures distance using an ultrasonic sensor.
- Maps the measured distance to a value between 0 and 7.
- Lights up LEDs via a shift register to represent the measured distance.
- Includes several LED animation patterns as functions that one could use.

## Hardware

- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- 74HC595 Shift Register
- 8 LEDs
- Resistors (for LEDs)
- Breadboard and jumper wires

## Pin Connections

| Arduino Pin | Connected To                |
|-------------|----------------------------|
| 7           | HC-SR04 Echo               |
| 8           | HC-SR04 Trig               |
| 9           | 74HC595 SH_CP (Clock)      |
| 11          | 74HC595 ST_CP (Latch)      |
| 12          | 74HC595 DS (Data)          |

## How It Works

1. The ultrasonic sensor measures the distance to an object.
2. The distance is mapped to a value between 0 and 7.
3. The corresponding number of LEDs are lit up using the shift register.
4. Serial output provides debug information.

## Getting Started

1. **Clone this repository**
2. **Install [PlatformIO](https://platformio.org/) in VS Code**
3. **Connect your hardware as described above**
4. **Build and upload the code:**
   ```
   pio run --target upload
   ```
5. **Open the Serial Monitor to view distance readings:**
   ```
   pio device monitor
   ```

## Library Dependencies

- [martinsos/HCSR04](https://platformio.org/lib/show/691/HCSR04)

These are managed automatically by PlatformIO via `platformio.ini`.

## File Structure

- `src/main.cpp` — Main Arduino code
- `platformio.ini` — PlatformIO project configuration
- `lib/` — For custom libraries (currently unused)
- `include/` — For project headers (currently unused)

## License

MIT License. See [LICENSE](LICENSE) for details.

---

*Created by kelenna udo*
