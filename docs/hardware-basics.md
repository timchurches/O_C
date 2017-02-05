# hardware basics

## in brief

- [Teensy 3.1 / 3.2 dev board](https://www.pjrc.com/teensy/) (Freescale MK20DX256 / 32-bit ARM Cortex M4).
- 4x precision CV outputs, 16-bit (TI [DAC8565](http://www.ti.com/lit/ds/symlink/dac8565.pdf)). 
- output range: -3v / +6v, "in-the-loop" compensated, for proper DC accuracy (+ 9 calibration points per channel, settable in firmware); +/- 0.2mV error across a 9 octave pitch CV range is achievable.
- 4x CV inputs, -3.5v / +6.5v, 12bit, 100k input impedance.
- 4x trigger/gate inputs, threshold ~ 2.5v, > 100k input impedance.
- two rotary encoders, with built-in push switches.
- two push buttons.
- 128 x 64 pixel 1.3" OLED display (with an SPI interface and SH1106 driver chip).
- trigger-to-quantised-output latency < 100 microseconds
- 16.67kHz internal timer (CPU overclocked to 120MHz), which is also the DAC update rate. the ADC is also read at 16.67kHz but in several of the o_C "apps", 16 values are averaged to remove noise, meaning that the effective sample rate for CV inputs is about 1 kHz. Digital (gate/trigger) inputs are read at 16.67 KHz - this ensures very low latency.
- +/-12V power only, ca. 85mA power draw on +12V bus, much less on -12V bus)

## more details

- **o_C** is a fairly straightforward DAC breakout board for the (Arduino-compatible) **teensy 3.1/3.2** ARM development board (cortex M4), with an OLED display: 
somewhat like a pimped-up "ardcore", though its focus is on generating **precision control voltages** rather than being (entirely) general purpose (see the [schematic](https://github.com/mxmxmx/O_C/blob/master/hardware/o_c_rev2e_schematic.pdf) and note re SPI below). 

- to this end, the board features four **16-bit CV outputs**, courtesy of [DAC8565](http://www.ti.com/lit/ds/symlink/dac8565.pdf). The outputs (range: -3V/6V) are "in-the-loop" compensated to ensure proper **DC accuracy**, ie. to prevent any voltage errors when connected to (the usual) 100k input impedances downstream. with suitable equipment, it's feasible to tune the calibration points (9 per channel) accurate to +/- 0.0002V; ie **tracking shouldn't be half-bad**, at all (that's an error for pitch CVs of well under 1 cent, where a cent is one-hundredth of a standard semitone (1200 cents per octave) - the limit of human pitch difference detection is about 4 cents, thus the pitch CV tracking in O+C can be calibrated to be more accurate than your ear, or your VCOs).

- in addition, there are four CV inputs (~12 bit, -3V/6V range, 100k input impedance) as well as four digital inputs (> 100k input impedance, threshold ~2.5V), two encoders (w/ switch), and two tact switches.

- as the DAC shares the SPI port with the 128x64 **OLED display** (teensy 3.1/3.2 only has one such port), **the thing is less suitable** for applications that need to write to the DAC at audio (ish) sample rates (ie LFOs, ADSRs, etc). that said, with some DMA trickery, usable results are possible even in that direction (in fact, with pld's interleaved OLED/DAC driver, in the **ornaments & crimes firmware**, the update rate is 16.666kHz).

- the trigger-to-quantized-output **latency** is pretty decent (< 100us), too:

![](https://c2.staticflickr.com/2/1517/24481688162_261cea4a0b_b.jpg)

- scope screenshot (from ASR mode):  blue - trigger input; yellow - DAC channel #1 output; grid is 500us.

- the 8-pin header (OLED header) brings out the full set of SPI signals, ie incl. MISO/DIN (Teensy pin #12), which isn't needed for the display and DAC; in theory though, any other/any SPI device(s) might thus be attached instead (ie other than the OLED): ADCs, port expanders, etc., as happened, for example, [here](https://farm6.staticflickr.com/5597/15384902927_303c42cd7d_b.jpg), using an atmega328 as a SPI slave. a variation of this uses two MCP23S17s and illuminated tact switches. or pots be used instead of the encoders (more details re available pins below). the board could also be mounted vertically, as a 4-6HP module: there's two mounting holes.

- the original firmware implemented a quantizing ASR; other possible uses would include: 

  * ~~dual sequencer (abusing two outputs for gates)~~ -- implemented.
  * ~~quad S+H/quantizer~~ -- implemented in the ornaments & crimes firmware
  * ~~pitch CV generators~~ -- implemented in the ornaments & crimes firmware
  * usb-midi to CV stuff (teensies are easily turned into class compliant USB devices; though there's no socket on the panel, of course). 
 
============================================================================================

## disclaimer
- i drew the circuit **by hand** (which is to say, in pcb-view); the [schematic (rev 2e)](https://github.com/mxmxmx/O_C/blob/master/hardware/o_c_rev2e_schematic.pdf) is entirely **post-hoc**, though it should be (is) a fairly accurate reflection of what's going on. anyways, it's all generic digital module stuff, so fairly unexciting. here's the basics, more verbose (this pertains to 2d, 2e boards):

### output

- inverting op amp, - 4x gain and offset (V_bias = 1.25v):

      <img src="https://c1.staticflickr.com/9/8631/28192735124_a3b27861b8_b.jpg" width="75%">.

- V_ref/2 is formed by a voltage divider (the two 47k resistors marked with a `*`) and the DAC reference (2.5v), so V_bias = 1.25v. this will result in an output range from -3.75v (min) to 6.25v (max), or -3v to 6v in terms of the calibration points:

  `V_out = - 4 * V_dac + 5 * V_bias` 

- if you'd prefer a **different range**, you'll have to change the bias voltage, or the divider, for that matter. for instance, changing the input resistor (see below: the yellow one) to 22k results in V_bias = 1.703v (= 47/(47+22)*2.5v). the resulting range will be more like -1.5v to 8.5v, or -1v to 8v. should you prefer a fully positive output range (0-9v), a voltage divider formed from 15k and 47k should do the job: V_bias ~ 1.896v. (the calibration procedure won't know, of course, and not reflect those shifted ranges; it can still be used or if that's confusing, you'd just have to hack the displayed values. easy.).

   <img src="https://c1.staticflickr.com/1/679/23174597339_866f04521d_o.png" width="40%">.

- you can shift up (or down) the output range by changing the divider.

- versions **prior** to 2e: there's a trimpot per channel (labelled `2k`) in series with a 24k input resistor (to adjust the gain, ie 100/25 = 4): ignore those, and simply use **24k9** 0.1% resistors instead (details [here](https://github.com/mxmxmx/O_C/wiki/build-it#nb--jumpers)).

### CV inputs 

- inverting op amp with negative offset, from AREF (LM4040-5):

    <img src="https://c2.staticflickr.com/8/7430/27750156762_e7855b10cb_o.png" width="90%">.

- the offset is ~ 6/9 of the ADC range (3.3v) or ~2.2v, so the inputs will match the DAC output range (-3v/6v).
- (so, alternatively, a LM1010-10 (AREF = -10v) and 150k resistors could be used instead: 
    `-(33k/75k * -5v) = -(33k/150k * -10v)`. 
- the range can be adjusted (should you prefer) by substituting the 75k resistor: 100k will yield a fully bipolar range (-5v/5v), 49k9 will yield ~ 0-10v. 
- note: the silkscreen (wrongly) says `49k9` where is should say `75k`. (fixed in 2e)

### digital inputs 

- using (NPN) transistor 'switches'. ie collector tied to 3V3 via a series resistor; emitter to ground; the trigger signals go into the base via a 100k series resistor and 33k to ground.
- as of rev 2.c the internal pull-up resistors are used (50k, ish):

<img src="https://c2.staticflickr.com/6/5794/22739727543_a5f7b4fc28_c.jpg" width="60%">.

### encoders 

- the encoders use pins 14, 15, 16 resp. 21, 22, 23 (any or all of these pins could be wired as/to potentiometers); the two tact switches use pins 4 and 5. here's the teensy pinout for reference: 

<img src="https://www.pjrc.com/teensy/card5a_rev7.png" width="60%">.
