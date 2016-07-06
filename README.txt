README

Set of C++ classes for speed and position control of DC motors using quadrature 
encoders and an Arduino or similar microcontroller.

An instance of Motor provides control of the direction and voltage to a single 
DC motor by means of a motor driver such as a TB6612FNG. The constructor for 
Motor takes 3 ints as arguments: the numbers of the 2 digital pins used to 
control the motor’s direction and the number of the PWM pin used to control 
the voltage to the motor. 

An instance of Encoder reads the output of a single quadrature encoder. The 
constructor takes 3 ints and a long as parameters: the numbers of the 2 digital 
pins connected to the encoder’s outputs, the time interval used for speed 
measurements in microseconds, and the number of encoder ticks per revolution of 
the motor’s output shaft. Encoder.updateCount() must be called with an interrupt
on encoder pin A; see the example sketch for detail.

As instance of SpeedControl provides PID speed control of a single DC motor. 
The constructor takes a pointer to an instance of Motor and a pointer to an 
instance of Encoder as parameters. Uses default PID gain values of 1.0 unless 
gains are set using the SpeedControl.setGains() function. If position control 
is not required, SpeedControl can be used on its own. In this case 
SpeedControl.adjustPWM() should be called using a timer interrupt with a 
period equal to the time interval used by the Encoder object.

An instance of PositionControl provides approximate position control and 
PID speed control for a DC motor. The constructor takes a pointer to an 
instance of SpeedControl as a parameter. PositionControl.adjustPWM() should 
be called using a timer interrupt with a period equal to the time interval 
used by the Encoder object. If PositionControl is used, the 
SpeedControl.adjustPWM() method should not be used.
