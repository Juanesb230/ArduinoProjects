# Arduino Projects
<!-- markdownlint-disable MD033 -->
<!-- markdownlint-disable MD047 -->
## 1. SPWM

<p align="justify">
This code in the dca folder generates a SPWM with Arduino. The following figure shows the scheme was done.
</p>

<p align="center">
  <img src="Images/dca_1.PNG">
</p>

<p align="justify">
And the other figures show the generated signals.
</p>

<p align="center">
  <img src="Images/dca_2.PNG">
</p>

## 2. Position PID control at Stepper Motor

<p align="justify">
This code in the stepperPIDcontrol folder has position control with a PID. The sensor that measures the position is a potenciometer and the output signals is by using the ULN2003 driver.
</p>

## 3. XBEE send a DATA

<p align="justify">
This code in the xbee_sendData sends a string DATA with Zigbee protocol.
</p>

## 4. XBEE PID position control

<p align="justify">
This code in the xbeePIDServo360control folder has a position controller for a continuous servo. The feedback sensor is a rotative encoder, the senpoint is sending by a computer with ZigBee Protocol and the arduino send to computer the encoder position data. The figure shows the prototype.
</p>

<p align="center">
  <img src="Images/XbeePID.PNG">
</p>

## 5. Treadmill Prototype

<p align="justify">
In the folder you can see two fields, the arduino code and the Proteus field for the simulation. In this project is used:
 -Arduino MEGA 2560
 -LCD 16X2
 -DS1307
 -DC Motor
 -Optical Encoder
This Treadmill Prototype has a different tranining modes, before it starts the user enters his weights and calculates the calories of him. The arduino EPROM saves a history of data and the DS1307 manages time for up to a week. The followinf figure shows some functions.
</p>

<p align="center">
  <img src="Images/Treadmill.PNG">
</p>

## 6. Energy calculation and send it by NRF24L01

<p align="justify">
With an Arduino, voltage and current sensors the code calculates the energy and sends that data with NRF24L01.
This code receives a message of RPI and sends the energy. The RPI code is in the following link:
</p>

<https://github.com/Juanesb230/RaspberryProjects/tree/master/NRF24L01communication>

The next figure shows the energy sent with NRF24L01.

<p align="center">
  <img src="Images/NRF.jpg">
</p>

## 7. Contact with me

Linkedin: <www.linkedin.com/in/juan-balseca-pinto-9117b397>