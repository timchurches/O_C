---
title: calibration
layout: default
---

- Calibration mode lets you fine-tune the **CV outputs** and **inputs** as well as adjust some basic settings: 
  - display offset
  - encoder direction
  - screensaver timeout period

- The calibration menu is entered by keeping the **left encoder** pushed down during start up / power-on.

- To adjust the DAC code, you'll need a **good multimeter**; ideally, 40000 counts or better (often described as 4 3/4 digits or better).

- Note that at each step, you click the **right encoder** to proceed, or click the left encoder to go back one step. Rotating the **left encoder** clockwise also advances through the calibration steps, and anticlockwise steps back through the calibration steps.

### 0. setting encoder directions

- Depending on the PCB revision and/or brand of encoder you've used, the encoders might turn in the wrong/reverse direction. If your encoders - left, right, or both encoders - happen to turn in the **reverse direction**, this can be easily fixed by pressing the **lower tact switch** once (or twice, or thrice) while in calibration mode. The effect is immediate and will cycle through the following options:

    `"normal", "R reversed", "L reversed", "LR reversed"`

- Keep pressing the lower button until you find the right setting for your hardware (there are only four possible permutations, as listed above).

- Be sure to store your calibration settings on the last calibration screen (see below) so that the encoder direction setting is **persistent** - you should never need to set it again unless you revert to the default calibration settings at some stage.

### 1. use default values?
- The first screen asks whether to use **default values** or not. If this is the **first time** you calibrate the module, or if you wish to re-calibrate from scratch, select `Yes` and click (press) the right encoder to proceed. Otherwise, if you just want to adjust or fine-tune your **existing calibration settings**, select `No` and then click the right encoder.

### 2. correct display offset?
- The next screen allows you to adjust the **display position**: some OLED screens are offset by two pixels, some are not (SH1106 vs SSD1306, typically). You should see a **complete rectangle** around the perimeter of the screen. If not, twist the right encoder until you do, then click the right encoder to proceed.

### 3. calibrate DAC channels A-D (= fine-tune the DAC code):

NB: the channels map to the panel as follows: A (top left), B (top right), C (bottom left), D (bottom right).  

- Start with **channel A**: connect your multimeter to the channel A output (typically using alligator clip connectors on a patch cable inserted in the channel A jack, or some other equivalent arrangement). 

- The next screen (or the first calibration screen) will have a heading saying `DAC A -3 volts`; twist the right encoder until you see exactly -3.0000 volts on the A output. The display on your multimeter (make sure it is set to high resolution mode) might jump around between -2.9999 and 3.0000, or between -3.0000 and -3.0001. That's fine, just get it as close to -3.0000V as possible. Click the right encoder to proceed.

- The next screen will be similar, but the heading will have changed to `DAC A -2 volts`. Once again, twist the right encoder until the output of channel A is as close to -2.0000V as possible. Click the right encoder to proceed.

- Continue these steps, adjusting the output of **channel A** in 1 volt increments all the way up to +6.0000V. If your multimeter has only 40,000 counts of precision, then it will drop back to 1 millivolt resolution above 4 volts. Just try to get as close as you can to exactly 5.0000V and 6.0000V. Generally, just a few notches of encoder rotation past the point where the display flicks over from, say, 4.999 to 5.000 is the correct point. If your meter has greater resolution (such as 5 1/2 digits), then you will be able to accurately measure down to the nearest 0.1mV and get the adjust exactly right. Note the progress bar at the bottom of the screen shows how many steps have been completed.

- The procedure is then repeated for **channel B**, then for **channel C**, and finally for **channel D**.

### 3. calibrate CV inputs:

- After the DAC channel D adjustments have been completed, the next step adjusts the **CV input offsets for each channel**. With no inputs connected, twist the right encoder so that the value shown is as close to 0 as possible. There may be some jitter and it might jump around between -1 and 0, or between 0 and 1 - that's fine - just get it as close to zero as possible. **Repeat this for all four CV inputs.**

- Next, you need to adjust the **CV input scaling** at 1 volt. To do this, you need a reference voltage of *exactly* 1 volt. Luckily, we have already calibrated the module outputs by this stage, so we can just use those. Exactly 1.0000V should now be output on channels A to D (check this with your meter, and choose the channel with the voltage nearest 1.0000V). **Connect this channel output to the CV1 input** using a patch cable, and long-press the right encoder to record the offset value.

- Repeat this for the 3V reference point (at this point +3.0000V will be output on channels A to D).

### 4. screensaver timeout period:

- adjust to your liking.

### 5. save 

- Finally, **save** the results (by clicking the right encoder). 

- Power-cycle, and you're set.
