# arduino-vas
Vehicle Augmentation System

My current embedded electronics project takes the form of a chaotic arduino powered mess of wires, breadboard and some other straing feelings. Right now its only purpose is to display my intake manifold pressure (or boost pressure). However, I have some intended features that will truly allow it to live up to its name.

Intended Features
=

Onboard WiFi
-
WiFi would probably be run by an external device. Such as a tablet running custom code to provide a wireless network and control convenience functionality on the car.

Coolant Heater Control
-
Most people control their electric coolant heaters through the use of standalone christmas light timers, a IoT enabled switchable outlet or by simply plugging in their car manually when they want to start heating it. These methods are fairly easy to implement and use, which means I need my own way. What I would like to implement is a system that will activate the mains powered coolant heater when A) The temperature requires it and B) When the schedule permits. Although it would be nice to have the heater powered via a self maintained power source such as the vehicles battery or electrical contacts in the parking stall it's simply not easily doable. I'll still have to plug in the car when it's parked but atleast the control will be onboard and won't require any other devices to be plugged routinely.
