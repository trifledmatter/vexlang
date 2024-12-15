---
# VEXLANG - Real-Time DSL for VEX v5

## Abstract

VEXLANG is a DSL (domain-specific language) layer built on top of the VEX v5 ecosystem. It fixes the fact that you can't talk to a VEX robot dynamically over serial. This project is basically a VEX app that sits there, listens to serial commands, and does what you tell it to. Serial input becomes robot actions. It's clean, modular, and kind of cool if you like robots.
---

## What It Does

Controlling VEX robots with the usual methods is annoying because they don't listen to serial input in real time. VEXLANG fixes that. It’s a layer that interprets commands, figures out what you meant, and makes the robot do it. You type something like "vex motor 1 set 100," and the robot sets motor 1 to speed 100. That’s it.

It uses the PROS library to handle all the hardware stuff and a bunch of commands to make things work dynamically. If you need real-time debugging, prototyping, or just want to tinker, this is for you.

---

## Why It’s Useful

The VEX API doesn’t support real-time serial command execution. VEXLANG bridges this gap by:

1. Running a listener in the background to handle serial input.
2. Mapping input to predefined commands.
3. Sending feedback back to you through serial or the robot's screen.

This is useful for quick testing, prototyping, or just yelling at your robot.

---

## Installation and Setup

### Requirements

- [PROS CLI](https://pros.cs.purdue.edu/v5/cli/)
- A computer with a serial port.

### Steps

1. Clone this:
   ```bash
   git clone <repository_url>
   ```
2. Build it:
   ```bash
   pros make
   ```
3. Upload it to your robot:
   ```bash
   pros upload
   ```
4. Open a serial terminal (or use the Python script provided).

---

## How to Use It

1. Run the program on your VEX robot.
2. Send commands like "vex motor 1 set 100" through serial.
3. Watch the magic happen.

---

### Command Format

```
vex <command_category> <identifier> <action> <arguments>
```

---

## Commands You Can Use

### Motors

Control individual or multiple motors.

| Command                          | What It Does                        |
| -------------------------------- | ----------------------------------- |
| `vex motor <m> set <speed>`      | Set motor `<m>` speed to `<speed>`. |
| `vex motor <m> stop`             | Stop motor `<m>`.                   |
| `vex motor <m> setDirection <d>` | Set motor `<m>` direction.          |
| `vex motor <m> setPosition <p>`  | Move motor `<m>` to position `<p>`. |
| `vex motor all stop`             | Stop all motors.                    |

Example:

```
vex motor 1 set 100
```

---

### Sensors

Get data or calibrate sensors.

| Command                     | What It Does                       |
| --------------------------- | ---------------------------------- |
| `vex sensor <s> getReading` | Get the reading from sensor `<s>`. |
| `vex sensor <s> calibrate`  | Calibrate sensor `<s>`.            |
| `vex sensor <s> reset`      | Reset sensor `<s>`.                |
| `vex sensor all reset`      | Reset all sensors.                 |

Example:

```
vex sensor 1 getReading
```

---

### Battery

Check your robot’s battery stats.

| Command                      | What It Does                            |
| ---------------------------- | --------------------------------------- |
| `vex battery getVoltage`     | Get the battery voltage in volts.       |
| `vex battery getCapacity`    | Get the battery capacity as a percent.  |
| `vex battery getTemperature` | Get the battery temperature in Celsius. |
| `vex battery getDiagnostics` | Get all battery info.                   |

Example:

```
vex battery getDiagnostics
```

---

### Robot

High-level robot stuff.

| Command                                    | What It Does                                             |
| ------------------------------------------ | -------------------------------------------------------- |
| `vex robot move <m1> <m2> <dist> <speed>`  | Move motors `<m1>` and `<m2>` for `<dist>` at `<speed>`. |
| `vex robot turn <m1> <m2> <angle> <speed>` | Turn the robot using `<m1>` and `<m2>`.                  |
| `vex robot stop`                           | Stop all movement.                                       |
| `vex robot reset`                          | Reset the robot state.                                   |

Example:

```
vex robot move 1 2 500 100
```

---

### Debugging

Turn debugging on/off.

| Command           | What It Does      |
| ----------------- | ----------------- |
| `vex debug start` | Starts debugging. |
| `vex debug stop`  | Stops debugging.  |

Example:

```
vex debug start
```

---

## Error Handling

When something goes wrong:

1. It tells you via serial.
2. It shows an error on the screen.
3. It doesn’t break (hopefully).

Example:

```
> vex motor 99 set 100
< Error: Invalid motor ID. Motor ID must be between 1 and 21.
```

---

## Adding Commands

1. Write a new class that inherits from `Command`.
2. Implement `execute` to do your thing.
3. Register it in `CommandManager`.

---
