# building the thing

![thething](https://c1.staticflickr.com/9/8016/29538793842_6a1f8160bd_c.jpg)

#### bill of materials (BOM)

- see [here](/O_C/bom_2d/) (2d, 2e) (red pcbs)
- see [here](/O_C/bom_2c/) (2c) (yellow pcbs)

#### shopping:

- for your convenience, here's a mouser [cart](https://eu.mouser.com/ProjectManager/ProjectDetail.aspx?AccessID=d2683e5a97) (2d, 2e). note: this has 20mm **D-shaft** encoders, **black** button caps (when using black panels, a different colour might be more [friendly to the eyes](https://c1.staticflickr.com/9/8016/29538793842_6a1f8160bd_c.jpg) (e.g. 642-1IS11-15.0, or 642-1IS11-16.0)), and **includes** the teensy 3.2 (which can be had cheaper at [oshpark](http://store.oshpark.com/products/teensy-3-1)); it **doesn't include** the 2x14 [header](http://www.ebay.com/itm/Single-Row-40Pin-2-54mm-Round-Male-Pin-Header-gold-plated-machined-J8-/301747757572)/[sockets](http://www.ebay.com/itm/3Pcs-Single-Row-40Pin-2-54mm-Round-Female-Pin-Header-gold-plated-machined-H-/301723646399), [thonkiconn](https://www.thonk.co.uk/shop/3-5mm-jacks/) jacks, 3M/hex screws, and the OLED display. re knobs: options include [sifam](https://www.thonk.co.uk/shop/intellijel-style-knobs/) (w/ "encoder caps"), [rogan 2s](https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/), and [cliff K85](https://www.google.com/search?q=CL17094) (+ suitable [cap](https://www.google.com/search?q=CL1709761)).

#### panels:

- current options include: DIY ([.fpd, .svg](https://github.com/mxmxmx/O_C/tree/master/hardware)), [common ground/KOMA](http://www.commonground.community/), [grayscale](http://grayscale.info/panels/mxmxmx-ornament-crime/), [magpie](http://magpie-modular.myshopify.com/products/ornament-crime-panels-pcbs), and [oscillosaurus](http://modularaddict.com/oscillosaurus-oc-panel).

#### schematic:

- see [here](https://github.com/mxmxmx/O_C/blob/master/hardware/o_c_rev2e_schematic.pdf) (2e) (2d, 2c is basically identical)

#### board revision change log: 

- see [here](/O_C/hardware-changelog/) (check in case of doubt)

#### component overlay:

- [rev.2e](https://c1.staticflickr.com/9/8717/28183612163_6b990a9d25_o.png) (red pcbs)
- [rev.2d](https://c2.staticflickr.com/2/1621/26682902275_05ee4e0aa1_o.png) (red pcbs)
- [rev.2c](https://c2.staticflickr.com/2/1572/26616844311_cb71c91ef4_o.png) (yellow pcbs)

#### troubleshooting: 

- [go here](https://github.com/mxmxmx/O_C/wiki/build-it#trouble-shooting).

#### notes:

- **make sure to take a look** at the note re: [OLED](https://github.com/mxmxmx/O_C/wiki/build-it#oled) below.

- NB: versions **prior** to 2e: 

  - 1) with the **exception of the four `75k` resistors** (which go where it says `49k9`), and the four `560p` caps (which should go where it says `10n`), you can follow the values **printed on the board**. no special precautions required otherwise. 

  - 2) **ignore the 3-pin header** adjacent to the 2x14 teensy header, it's not needed; neither is the SOT-23 part labelled `LM4040-2.5` (top side). **`Q`** is where the four NPN transistors go. 

  - 3) as noted in the BOM, it's preferable to use **0.1% resistors**, _not_ 2k trimpots for the output stage (= the stuff around the dual op amps) (that's **irrespective** of the version of the board that you might have). ditto for the input stage, **don't use the trimpot**, but `75k` resistors. 

# populating the board:
 
### typically, you'd do the ICs first:

 ![](https://c2.staticflickr.com/2/1640/26645912911_f70b26195a_c.jpg)

- be careful with the orientation of the OPA2172s: [white dot](https://c1.staticflickr.com/9/8717/28183612163_6b990a9d25_o.png) = pin 1:

![](https://c1.staticflickr.com/9/8687/28791500516_ee1950d607_b.jpg)

- that's also where the 0.1% resistors should go; the `100k` (0.1%) ones are the ones in parallel to `24k9`.

### ... followed by the passives:

 ![](https://c2.staticflickr.com/2/1552/26105991024_aa3647fa17_c.jpg)

- **note**: use 75k where it says 49k9! and ideally, 560p or less where it says 10n. (if it says so, silkscreen fixed in 2e)
- (and don't forget the ADP150 and passives on the **top side** of the board!)

### ... followed by the through-hole and mechanical parts:

 ![](https://c2.staticflickr.com/8/7312/27238854354_87399a09ed_k.jpg)

- inductor, 2x5 header, 22uF caps, diodes, sockets for teensy and the OLED. 
- note: 2x14 sockets w/ **round** pins (as pictured): because the PCB holes are **small**.
- 1x7 (or 1x8) socket for the OLED: standard **square** holes, but **low profile**: 

![](https://c1.staticflickr.com/9/8521/29004348081_6a16786a08_b.jpg)

- use either a 7 or 8 pin header, the OLED goes between the square pin (pin 1) and the one marked with `^` (pin 7); the rightmost signal (pin 8 =  teensy pin 12) is **unused**.

### NB: ... jumpers (2d and earlier):

 ![](https://c2.staticflickr.com/8/7334/27525488461_dee4b992b9_k.jpg)

- note the five **jumpers** across the 3-pin pads! (the gaps in question should be easily visible).

### jacks: 

- the jacks **share the ground pad**, _facing_ each other:

![](https://c1.staticflickr.com/9/8172/29614771526_2c62a90864_c.jpg)

### encoders: 

- NB: previous PCB revisions had holes that were too small for the lugs; in case you have such a PCB, just snip off the lugs; either way you'll need a bunch of washers so that things line up nicely: 

![](https://c1.staticflickr.com/9/8854/28533473560_6080e36b2e_c.jpg)

- keep in mind the threaded part is finite, so the preferred solution will somewhat depend on choice of encoder and panel thickness. (especially if using 15mm encoders, it might make sense to solder the encoders onto the **top side** of the board, leaving some space between the PCB and the body of the encoder. [like so](https://c2.staticflickr.com/8/7481/15840079890_d7bf79a39f_b.jpg)).

### OLED: 

- the OLED (7 pins) goes between pin 1 (ground) and the `^` mark: **ignore the right-most signal** (pin 8), that's DIN/MISO, which isn't needed for the display. 

- if using an aluminium panel, make sure that **the OLED pins don't touch the panel!** (ie, cut them flush with the pcb; and/or insulate with a piece of tape).

- also: **use a low profile socket!** you'll have to trim the pins somewhat (or replace them) so as to make things fit / line up with the other components (ie jacks, encoders):

![](https://c1.staticflickr.com/1/572/32512469312_22f4a74eb5_h.jpg)

- if your OLED refuses to sit properly, a suitably sized spacer (~ 6mm) will help:

![](https://c1.staticflickr.com/9/8309/28203377893_d7731be7c8_c.jpg)

### spacer:

- the spacer (10mm, ⌀ 3M) goes right next to the tactile buttons:

![](https://c1.staticflickr.com/9/8640/29045338993_1742d4cff3_c.jpg)

### finally. prepare + insert the teensy. 

- you have to **cut one trace** (†):

![](https://c1.staticflickr.com/1/540/31765026055_5d82bd0ae3_z.jpg)

- and solder the pin headers, which look like so:

![](https://c1.staticflickr.com/9/8393/28962728551_65bd3b7ce9_c.jpg)

### done. 

- before inserting the teensy, it'll make sense to check a few basic things, first. here's a few points to test:

![trouble](https://c1.staticflickr.com/9/8701/28030347874_725c6eb238_k.jpg)

----------

#### (†) (note): 

- cutting the trace is mainly a **precautionary** measure: it is to prevent people (you) from powering the teensy dev-board **simultaneously** from USB and the eurorack PSU **when updating the firmware** (or when "debugging" code via serial USB); this might have undesirable consequences. see the [T3.2 schematic](https://www.pjrc.com/teensy/schematic32.gif) for details.
- cutting the trace is **not** essential for the module to work. if you prefer, you can leave the trace intact as long as you remember to **disconnect** your module from the eurorack PSU when connecting a/the USB cable. in this case, the teensy will be powered solely from V_USB (= 5V) **via** the USB-cable, which will be just as fine for the purpose of occasionally flashing the MCU. 

----------

#trouble shooting

- if things don't work out as expected/intended, here's a few things that you might want to check:

    - if you've used a panel made from conducting material (e.g. aluminium), do the OLED pins touch the panel? (they shouldn't).
    - op-amps oriented correctly? (see the pic and component overlay linked above)
    - any solder bridges? (reflow tricky parts, just to make sure).
    - forgot to solder the components on the top side of the board (ADP150 etc)?
    - power rails and reference voltages doing ok? -- see above.

- **common symptoms** include:

   - all outputs are **stuck at ~ 6.25V**: in this case, communication with the DAC typically isn't working properly. double check (reflow) the **SPI signals** from the teensy to the DAC; that's DAC pins 9, 10, 11 in particular (also double-check DAC pins 13 - 16).  
   - only some of the outputs work properly: in this case, chances are something's off with the output stage (corresponding to the misbehaving channel). check the dual op-amps and surrounding passives.
   - the DAC seems to work (in principle), but **calibration points > 0V cannot be tuned properly** / are way off: in this case, typically one of the outputs is shorted into 0V. check the jacks for shorts.
   - some or all of the **CV inputs** aren't working correctly: to further diagnose, there's a **debug menu** which can be entered by long-pressing the right encoder (= enter app selection menu), and then clicking the left encoder. hit the left encoder three times to go to the ADC debug page, which shows the raw ADC values:
     - with **no** signals patched, the **rightmost** column should show a value of ca. ~ `2730` for _all_ four inputs: that's the voltage offset at the ADC pins (which should be: `2.2V =~ 2/3*3.3V < > 2730 =~ 2/3*4096`). 
     - if **none** of the channels shows a value of ~ `2730`, most likely there is no -5V offset: check the LM4040 is working properly/actually outputting -5V; also check the `100R` resistors on the top side of the PCB (forgot them? used 100**k** instead of 100R?); lastly, check the MCP6004: is this ok / working properly otherwise?
     - if only **some** of the channels don't show a value of ~ `2730`, check the `75k` resistors.
     - if the offsets are all ok (all channels showing ~ `2730`), but individual CV channels don't register a signal, check the `100k` (input) resistors.
   - some of **clock inputs** aren't working: check the four transistors and associated passives (in the lower right half of the PCB/where it says `Q`).
   - clock input `TR3` isn't working; if you're positive the transistor is ok: there's a via fairly close to the teensy VIN pin and the 10uF cap nearby. double-check there's no short there.
