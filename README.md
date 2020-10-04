# fibromatic
Automatic feathering massage for Fibromyalgia patients using Arduino, RPi and a Robotic arm 

![a gif describing the fibromatic in action](https://media0.giphy.com/media/61T89gKzCf5UDsnZFe/giphy.gif)

## Overview

### Arduino

*Note: the Arduino (ATMEGA328P) is part of the Robotic Arm kit*

The Arduino is connected to the 3 servos and to the RPi's UART. 

Pinout:
9 - Servo1
6 - Servo2
5 - Servo3
10 -> RPi GPIO14

### RPi 

In charge of running NodeJS for the web interface and sending commands over UART to Arduino. 

Pinout:
GPIO14 -> Arduino pin 10

![connections overview](https://github.com/omeriko9/fibromatic/blob/main/connections_diagram.png)

I used [Adeept's 5DOF Robotic Arm](https://www.adeept.com/adeept-arduino-compatible-diy-5-dof-robotic-arm-kit-for-arduino-uno-r3-steam-robot-arm-kit-with-arduino-and-processing-code_p0118_s0031.html) but only used 3 out of the 5, that way I could use the additional unused servo pins for serial communication between the Arduino and the RPi Zero.

## Installation

### Arduino 
 
**ArduinoCode** Folder - Use Arduino IDE to upload the code. Main sketch file is *main.ino*.
Note the pin numbers, in case you are using a different product than me.

### Raspberry Pi

I used headless RPi zero with Raspberry Pi OS. 
You can pre-configure WiFi SSID & key (by using wpa_supplicant file), and enable SSH in advance. That way you won't need to connect a keyboard and a screen after inserting the SD Card. Google for a guide on how to do it, here is an [example of one](https://core-electronics.com.au/tutorials/raspberry-pi-zerow-headless-wifi-setup.html)

**firbopi** is the NodeJS root folder. 
Install NodeJS (I used version 14) on the RPi, and run `npm install` on that folder.
Then you can start the server normally with `node app.js` or use watch to monitor file changes and run it with `npm run watch`.

Since you probably want the webserver to start on every boot, you might consider adding **webstart.sh** to the bottom of ~/.bashrc, this will make sure it will only run on the first login and not on every ssh connection you'll open to the RPi.

## Usage

NodeJS will listen on **port 3000** (you can change port in start.js by changing `portnumber` variable), so while in WLAN try to access `http://fibro:3000` from your mobile phone. This should bring up the web UI.

## Communication

The protocol between the RPi and the Arduino is very rudamentary. Data is being sent as a string of characters, with the following format:

**C SS D***

C  - 1 character for command
SS - 2 characters for size of data
D* - 0 or more characters of data

Possible commands are:
1,2,3 - set angle for servos 1, 2 and 3. Data is the absolute angel. Example: `103110` sets servo1 at angle 110 degrees
a,b,c - increase/decrease angle for servos 1, 2 and 3. Data is the relative angel. Example: `a03-30` sets servo1 -30 degrees relative to its current state.
i     - return arm to initial position

p     - stop/start plan 1 (for start, data should be 1. Example of start command: `p011`)

t     - stop/start plan 2 (for start, data should be 1. Example of stop command: `t010`)

m     - Enlarge servo1 (z plane) angle 

n     - Reduce servo1 (z plane) angle

4     - delay between plan's instructions

s     - servo2 (y plane) offset. Offset added to plan's instruction and makes the apparatus higher or lower.







