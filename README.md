# Kitchen Timer with MSP432 and Custom PCB

This project implements a kitchen timer system using the **TI MSP432 microcontroller** with a custom-designed PCB that includes **7-segment LEDs**, **capacitive buttons**, **FETs**, and a **buzzer**. The firmware was written in **C** using **FreeRTOS** to manage real-time tasks, while interrupt handlers update the displayed time on the LEDs in response to a timer IC.

## Key Skills and Technologies
- **PCB Design (Altium)**: Designed a custom PCB housing 7-segment LEDs, capacitive buttons, FETs, and a buzzer for the timer functionality.
- **Embedded C Programming**: Developed firmware in C to interface with hardware components including 7-segment LEDs and buttons.
- **FreeRTOS**: Utilized FreeRTOS to manage real-time tasks, ensuring smooth operation of the timer and handling user inputs.
- **Interrupt Handling**: Implemented interrupt service routines (ISRs) to handle timer IC interrupts, updating the display in real-time.
- **Peripherals & Interfaces**: Programmed to interface with the Timer IC and 7-segment LEDs for timekeeping, using FreeRTOS for task scheduling.
- **Capacitive Touch Input**: Integrated capacitive buttons for user input, including setting and controlling the timer.

## Project Overview
The kitchen timer system allows users to set and track time, which is displayed on **7-segment LEDs** attached to the custom PCB. The system uses **FreeRTOS** to schedule tasks for button input, timekeeping, and display updates. The **on-board Timer IC** generates interrupts every second, triggering the firmware to update the displayed time accordingly.

The timer is controlled via **capacitive buttons** that allow users to set the desired time, while the buzzer signals when the timer reaches zero.

## Features
- **Real-time Timekeeping**: Utilizes the Timer IC to keep track of time, updating the display every second.
- **Custom PCB Design**: Designed and implemented a PCB housing all the necessary components, including 7-segment LEDs, capacitive buttons, FETs, and a buzzer.
- **FreeRTOS Task Management**: Managed multiple real-time tasks, such as handling button input and updating the time display, using FreeRTOS.
- **Interrupt-based Time Updates**: Interrupt handlers respond to Timer IC interrupts every second to keep the displayed time accurate.
- **User-friendly Interface**: Capacitive buttons provide an intuitive way to set and control the timer.

## Hardware Requirements
- **TI MSP432 LaunchPad**
- **Custom PCB** (designed in Altium) with:
  - **7-segment LEDs**
  - **Capacitive Buttons**
  - **FETs**
  - **Buzzer**
- **Timer IC**

## Project Breakdown
### PCB Design
- Designed a custom PCB using **Altium**, housing the necessary components (7-segment LEDs, capacitive buttons, FETs, and buzzer).
  
### Firmware Development (C, FreeRTOS)
- **C Programming**: Wrote firmware to interface with 7-segment LEDs, capacitive buttons, and the Timer IC.
- **FreeRTOS**: Utilized FreeRTOS to handle multiple concurrent tasks efficiently:
  - Button press detection.
  - Timekeeping logic.
  - Real-time updates to the display.

### Interrupt Handling
- Implemented an interrupt handler to process Timer IC interrupts every second, updating the time displayed on the LEDs in real-time.

### User Input and Control
- Used **capacitive buttons** to allow users to easily set the timer duration and start/stop the timer.
- Integrated a **buzzer** to sound when the timer reaches zero.

## Technical Skills Demonstrated
- **Altium PCB Design**: Designed a PCB with multiple components (LEDs, buttons, FETs, buzzer).
- **Embedded C Programming**: Developed the timer’s firmware to interface with multiple peripherals.
- **FreeRTOS Task Management**: Managed multiple tasks such as button input and display updates using FreeRTOS.
- **Interrupt Handling**: Developed ISRs to handle time updates triggered by the Timer IC.
- **Capacitive Touch Input**: Integrated capacitive touch buttons for user interaction.
- **Real-time Embedded Systems**: Worked in a real-time environment where accurate timekeeping and responsive input/output were critical.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/Kitchen-Timer.git
