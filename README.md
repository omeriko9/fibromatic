# fibromatic
Automatic feathering massage for Fibromyalgia patients using Arduino, RPi and a 3DOF servo based Robotic arm 

![a gif describing the fibromatic in action](https://media0.giphy.com/media/61T89gKzCf5UDsnZFe/giphy.gif)

## Overview

Arduino - connected to the robotic arm (3 servos) and to the RPi's UART. 
Pinout:
9 - Servo1
6 - Servo2
5 - Servo3
10 -> RPi GPIO14

RPi - Running NodeJS for the web interface, sending commands over UART to Arduino. 
Pinout:
GPIO14 -> Arduino pin 10

![connections overview](https://github.com/omeriko9/fibromatic/blob/main/connections.png)

I used [Adeept's 5DOF Robotic Arm](https://www.adeept.com/adeept-arduino-compatible-diy-5-dof-robotic-arm-kit-for-arduino-uno-r3-steam-robot-arm-kit-with-arduino-and-processing-code_p0118_s0031.html) but only used 3 out of the 5, that way I could use the additional unused servo pins for serial communication between the Arduino and the RPi Zero.







