# PES-Final-Project

**Objective:**

Implement the MMA8451Q accelerometer over I2C, and develop the logic for a digital
angle gauge without the LCD screen. LED color is changed in response to the device
orientation allowing a user to set the saw blade on a table saw to exactly 45° relative to the
table. Calibrate the sensor to 0° setting to improve the accuracy by using a button connected to
GPIO to indicate 0° or by sending a command over UART.

**Implementation:**

State machine:

State machine was implemented to change the state from calibration to angle_measurement.
There are three states present:
1. OBTAIN_DATA_ZERO_CALIB: This is the initial state where the accelerometer data is considered only if the default angle obtained by the accelerometer is zero.
2. CALIBRATE_ANGLE: This state is entered if the calibrate command is received or the GPIO pin PD7 is made to ground
3. ANGLE_DATA_DISPLAY: This expression is entered calibration in first two cases was successful. In this state the angle data is read. 

![statemachinecorrect](https://user-images.githubusercontent.com/91862302/206840850-7da09bd8-9b21-46dc-89ba-ee8379fe55d5.PNG)


The detection of signals is detected by the change of color. The following colors are used for detection:

a. Red color on the controller represents it is 30 degrees</br>
b. Green color on the controller represents it is 45 degrees</br>
c. Blue color on the controller represents it is 60 degrees</br>
d. White color on the controller represents it is 90 degrees</br>

The change of color is obtained by using PWM.

**Verification:**

The change of angle is manually tested by placing the sensor at angles like 30, 45 , 60 and 90 degrees.
The calibration is tested manually by giving calibrate command and validating if the that angle is reading a zero.
The PWM is tested by an automated test script written which tests if the LED glows correctly.

**Note**:</br>
The UART configuration used was:</br>
1. Baud rate: 38400</br>
2. Parity bit: None</br>
3. Stop bit: 2</br>

