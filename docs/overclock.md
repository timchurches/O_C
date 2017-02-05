# overclock. 

###instructions for teensyduino versions prior to 1.30:


- overclocking is required to increase the SPI clock to 30MHz / make the firmware run properly.

- to do so, find the file called **boards.txt**. on OSX, it lives in your Arduino.app folder: 

   `/Applications/Arduino.app/Contents/Java/hardware/teensy/avr/boards.txt `

    - (the path will be slightly different on linux or windows systems, of course).

    - now, **uncomment the line** that says: 

    `teensy31.menu.speed.120opt=120 MHz optimized (overclock)` 

    - (while you're at it, you may also want to change the optimization level: **-o2**)

    `teensy31.menu.speed.120opt.build.flags.optimize=-O2`

    - restart the arduino IDE.
    
