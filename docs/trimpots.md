---
title: calibration with trimpots
layout: default
---

- Go the page saying `DAC A -3 volts`. Connect your multimeter to the channel A output (typically using alligator clip connectors on a patch cable inserted in the channel A jack, or some other equivalent arrangement). If you push the the right encoder again, you'll see `DAC A -2 volts` and so on. Pushing the left encoder will take you back one step; you should also see the CV output for that channel move up and down by approx. 1 volt. Ignore what else is being said on the display for the time being: **at this point**, we'd like to adjust the gain, so that **1 volt steps** are seen at the **outputs**. 

- Calibrate one output at a time, **using the respective trimpot** on the back. Go back and forth in the menu until the steps are close to being 1v apart. Don't worry if the distance isn't exactly 1.0000v and don't worry about offset (eg 2.0034v, 3.0042v,...), we'll take care of that later; at this stage we're interested in getting it **pretty much right**. Repeat for each of the four channels. It is rather tedious, which is why building with 0.1% resistor and no trimpots is to be preferred. When done, proceed to fine-tuning the DAC code.
