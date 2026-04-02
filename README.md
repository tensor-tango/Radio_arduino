FM-Radio reciever based on Arduino Nano and FM Module TEA5676

Schematics can be found in the schematics.png, CAD files to be added soon.

In the schematics a condensator on the 7-segment-display is used to stabilize power lines, without it voltage and current are unstable, so that the whole system malfunctions.

In the firmware direct control of I2C is used to get rid of background I2C bus noise

During the field test the power supply to the whole system was provided via USB connection to the laptop. External power sources were not used, but coul be easily added to the system.

Amplifier is not included and the original audio output from TEA5676 was used. If audio amp is to be added, it should be definitely be powered from the external power sources. Using in-built Arduino's power lines to power the amp will cause the irreversive death of the Arduino, as it's powerlines are not meant to be used for such currents.

