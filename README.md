# STM32F407 — HAL Peripheral Projects

A collection of STM32 firmware projects built using STM32Cube HAL libraries 
and STM32CubeMX configuration, developed during my embedded systems work 
at Loginware Softwares.

> **Note:** These projects were developed and tested on STM32F407VGTx 
> hardware during my internship/work period. Hardware is not currently 
> in my personal possession, so live demo photos/videos are not available 
> for these specific projects. Circuit connections are documented via 
> pinout tables derived from the .ioc configuration files.

---

## MCU Target
**STM32F407VGTx** — ARM Cortex-M4 with FPU, 168 MHz, 1 MB Flash, 192 KB SRAM

## Toolchain
STM32CubeIDE, STM32CubeMX, STM32Cube HAL Drivers

---

## Projects

### 1. Display Drivers
| Project | Interface | Description |
|---|---|---|
| OLED_SSD1306_I2C | I2C | Driving SSD1306 128x64 OLED display via I2C using HAL |
| LCD_I2C_PCF8574 | I2C | 16x2 character LCD via PCF8574 I2C backpack expander |
| LCD_Parallel_HD44780 | GPIO (Parallel) | 16x2 character LCD in 4-bit parallel mode |

### 2. Sensor Interfacing
| Project | Interface | Description |
|---|---|---|
| DHT11_Temperature_Humidity | GPIO (1-Wire) | Reading temperature/humidity from DHT11 sensor |
| Ultrasonic_HCSR04_Distance | GPIO (Trigger/Echo) | Distance measurement using HC-SR04 ultrasonic sensor |
| DHT11_with_OLED_Display | GPIO + I2C | Combined sensor reading with live OLED display output |

### 3. Timers
| Project | Description |
|---|---|
| HAL_Timer_Configuration | Hardware timer setup using HAL timer handles, prescaler/auto-reload configuration |

### 4. Complete Projects
| Project | Description |
|---|---|
| Smart_Visitor_Head_Counter | IR beam-break sensor based visitor counting system with real-time LCD display output |

---

## How to Build
1. Open the .ioc file in STM32CubeMX to view/regenerate pin configuration
2. Import the project into STM32CubeIDE
3. Build and flash to an STM32F407-based board (e.g., STM32F4 Discovery)

---

## Related Project
For the complete dual-MCU WiFi scanning system (STM32 + ESP32), see:
[STM32-ESP32 WiFi Selector](https://github.com/Abhicm14/STM32-Project)
