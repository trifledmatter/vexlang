# VEXLANG - Real-Time DSL Layer on top of the VEX v5

## Abstract

**VEX Lang** is a domain-specific language (DSL) layer and command-based interface for enabling real-time control of VEX robotics hardware. Designed to overcome the inherent limitations of VEX robots in handling real-time serial communication, this project acts as a VEX application that continuously listens for serial commands and executes them dynamically. VEX Lang transforms serial input into actionable robotics commands, allowing for seamless integration of real-time interactions, modular extensions, and robust error handling.

---

## Introduction

Controlling a VEX robot through traditional means can be cumbersome due to the lack of support for direct, real-time serial interactions. Developers are often limited by low-level APIs and rigid control structures, making it impractical to achieve real-time feedback and action. **VEX Lang** addresses this fundamental limitation by providing a DSL layer, enabling the robot to listen for serial commands, interpret them, and execute corresponding actions dynamically during runtime.

By combining the VEX PROS library with a robust command management system, VEX Lang creates an interface that abstracts hardware operations into human-readable commands. This system is ideal for robotics developers, educators, and researchers seeking to prototype, test, or control robots dynamically.

---

## Core Problem

The VEX ecosystem lacks a native mechanism for dynamically interpreting serial input and executing hardware operations in real time. This project bridges that gap by:

1. Implementing a listener task that continuously processes incoming serial commands.
2. Mapping these commands to predefined actions using a modular and extensible command framework.
3. Providing real-time feedback via serial responses and on-screen updates.

---

## Features

- **Dynamic Command Execution**: Interpret and execute serial commands in real time.
- **Extensible DSL**: Add custom commands to control motors, sensors, and other hardware.
- **Error Handling**: Comprehensive error reporting for invalid commands or hardware issues.
- **Feedback Mechanism**: Real-time responses via serial output and robot screen updates.
- **Modular Design**: Framework for seamlessly adding new hardware commands.

---

## Installation and Setup

### Prerequisites

- [PROS CLI](https://pros.cs.purdue.edu/v5/cli/) for VEX development.
- A computer with a serial interface (e.g., USB).

### Installation

1. Clone the repository:
   ```bash
   git clone <repository_url>
   ```
2. Build the project:
   ```bash
   pros make
   ```
3. Upload the project to the VEX robot:
   ```bash
   pros upload
   ```
4. Connect to the robot's serial port using your preferred terminal or the provided Python script.

---

## Usage

### Workflow

1. Start the VEX application on the robot. It will enter "listening mode," waiting for serial commands.
2. Send commands via a serial terminal or a custom interface (e.g., the provided Python script).
3. The robot executes commands in real time and sends feedback via serial responses or on-screen updates.

---

### Command Syntax

Commands are structured as follows:

```
vex <command_category> <identifier> <action> <arguments>
```

#### Components

- **command_category**: The hardware or subsystem to control (e.g., `motor`, `sensor`).
- **identifier**: Specifies the target component (e.g., motor ID, sensor ID, `all`).
- **action**: The operation to perform (e.g., `set`, `calibrate`).
- **arguments**: Additional parameters required by the action.

---

## Command Reference

### 1. **Motor Commands**

Control individual or multiple motors dynamically.

| Command                          | Description                                              |
| -------------------------------- | -------------------------------------------------------- |
| `vex motor <m> set <speed>`      | Sets motor `<m>` to a specific speed.                    |
| `vex motor <m> stop`             | Stops motor `<m>`.                                       |
| `vex motor <m> setDirection <d>` | Sets the direction of motor `<m>` (`forward`/`reverse`). |
| `vex motor <m> setPosition <p>`  | Sets the position of motor `<m>` to `<p>`.               |
| `vex motor <m> setPower <p>`     | Sets the power of motor `<m>` to `<p>`.                  |
| `vex motor all stop`             | Stops all motors.                                        |

**Example:**

```
vex motor 1 set 100
```

### 2. **Sensor Commands**

Retrieve or calibrate sensor readings in real time.

| Command                     | Description                              |
| --------------------------- | ---------------------------------------- |
| `vex sensor <s> getReading` | Retrieves the reading from sensor `<s>`. |
| `vex sensor <s> calibrate`  | Calibrates sensor `<s>`.                 |
| `vex sensor <s> reset`      | Resets sensor `<s>`.                     |
| `vex sensor all reset`      | Resets all sensors.                      |

**Example:**

```
vex sensor 1 getReading
```

### 3. **Battery Commands**

Monitor battery diagnostics dynamically.

| Command                      | Description                                    |
| ---------------------------- | ---------------------------------------------- |
| `vex battery getVoltage`     | Displays the battery voltage in volts.         |
| `vex battery getCapacity`    | Displays the battery capacity as a percentage. |
| `vex battery getTemperature` | Displays the battery temperature in Celsius.   |
| `vex battery getDiagnostics` | Displays all battery diagnostics.              |

**Example:**

```
vex battery getDiagnostics
```

### 4. **Robot Commands**

Perform high-level robot operations like movement and rotation.

| Command                                    | Description                                               |
| ------------------------------------------ | --------------------------------------------------------- |
| `vex robot move <m1> <m2> <dist> <speed>`  | Moves motors `<m1>` and `<m2>` for a distance at a speed. |
| `vex robot turn <m1> <m2> <angle> <speed>` | Turns the robot using motors `<m1>` and `<m2>`.           |
| `vex robot stop`                           | Stops all robot movement.                                 |
| `vex robot reset`                          | Resets the robot's state.                                 |

**Example:**

```
vex robot move 1 2 500 100
```

### 5. **Debug Commands**

Enable or disable debugging modes.

| Command           | Description       |
| ----------------- | ----------------- |
| `vex debug start` | Starts debugging. |
| `vex debug stop`  | Stops debugging.  |

**Example:**

```
vex debug start
```

---

## Error Handling

A global error-handling system ensures robust command execution:

1. **Input Validation**: Invalid commands return usage messages.
2. **Runtime Exceptions**: Unexpected errors are caught and reported.
3. **Feedback Mechanism**: Errors are displayed on the robot screen and sent to the serial interface.

**Example:**

```
> vex motor 99 set 100
< Error: Invalid motor ID. Motor ID must be between 1 and 21.
```

---

## Development Guide

### Adding New Commands

1. Create a new command class inheriting from `Command`.
2. Implement the `execute` function to define the command’s behavior.
3. Register the command in the `CommandManager`.

**Example:**

```cpp
commandManager.registerCommand(std::make_unique<YourNewCommand>());
```

---

## Acknowledgments

This project leverages the [PROS library](https://pros.cs.purdue.edu/v5/) for VEX robotics development. It is inspired by the need for a more dynamic and modular approach to robot control and experimentation.
