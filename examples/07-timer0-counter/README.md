This example show how to use the Timer0 to count how many times a 
button has been pressed.

When a button connected over P3.4 (external T0) and when pressed
set pin to GND (by default P3 will be pull-up) it will count 
how many times was pressed (note that it can count more since there 
is no way to avoid button bouncing)
