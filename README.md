# Arduino_encoder_midi
Arduino Leonardo 2 encoders - usb midi - do2 or ma2 ma3 ? :D


This is a very simple code for handling an encoder and USB MIDI. The code was written for Arduino Leonardo - but you can use any model that supports MIDI communication via USB.

You might be surprised by the pin definitions - but I wrote it this way so you can test it without additional hardware. I simply connected the encoder directly to the Arduino pins and started working.

This is the basic version - which I expanded to 2 encoders - but of course, you can use more of them. The encoder readings are done in the loop - and thanks to my idea, it works exceptionally well and doesn't make mistakes like often seen in examples.

Of course, interrupts can be applied - (CLK + DT) - but this is not necessary - because this code works very well without interrupts and without delay or debounce!

The code is specially prepared for MA software - grand ma2 or dot2.

It sends MIDI messages which are easily recognized and you can directly enter the appropriate commands to control the encoders in the Remote Input line.

Each encoder sends a NoteON message with a value of 127 - when turning left, one note, and when turning right, another. The same goes for the second encoder.

Notes are defined at numbers 123 124 125 126.

I didn't need the encoder button - but you surely know how to add it yourself.

Happy testing!
