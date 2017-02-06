---
title: firmware chnagelog
layout: default
---

#### Changes between v1.1 and v1.2
* General operation
  * added a _saving..._ confirmation message when settings are saved. The module now pauses operation momentarily during the settings save procedure

* _CopierMaschine_
  * added Turing Machine, Bytebeats and Integer Sequences internal CV sources, with external voltage control over their parameters

* _Harrington 1200_
  * added N, S and H secondary (compound) chord transformations, in addition to the existing atomic P, L and R transformations
  * made external voltage control over all main parameters mappable, instead of hard-coded to specific inputs
  * voltage control of transpositions can be made to take effect only on trigger inputs, making it easier to synchronise transpositions with the "beat"
  * added "Euclidean trigger masks" (trigger filters) which allow complex patterns of chord transformations using P, L, R, N, S and H transformations to be created from a single regular clock input. Parameters for these Euclidean trigger masks can be modulated with external mappable control voltages to allow chord progression changes to be externally influenced.

* _Quantermain_
  * added Integer Sequences as an additional internal CV source (these are the same as the integer sequences added to _CopierMaschine_). Available integer sequences include digits of transcendental mathematical constants, and fractal and semi-fractal integer sequences. External voltage control of several parameters for each of these sequences is provided.
  * added octave transposition up or down via a gate signal on each of the trigger inputs (TR1 to TR4) when in continuous quantisation modes (feature suggested by _timoka_ on MW).
  * unused inputs can now be re-mapped to basic channel parameters (`root`, `octave`, `scale mask`, etc) (ie, when using inputs other than the nominal/default sample input).

* _Quadraturia_
  * added several slower speed ranges, with the slowest ("cosmological") taking over 18 hours to complete one cycle.
  * added `Output range` and `Offset` parameters, affecting all channels, to permit unipolar output without having to use external voltage processors.

* _Piqued_
  * segment duration multiplier settings have been added, one each for the attack, decay and release segments. The duration multiplication goes from 1 to 8192, making very slow envelopes possible.
  * The `Hard Reset` setting has been split into two settings, one which affects the attack segment, and the other which affects the decay and release segments, and 45 different behaviours can be specified for each. This allows fine-tuning of the reset (re-trigger) behaviour when a new trigger/gate is received while an envelope is still in progress.
  * added overall envelope `Amplitude` setting, and ability to use external control voltages for this, as well as a setting (`Sampled Ampl`) which determines whether the overall amplitude level is set continuously or just sampled each time a new trigger/gate is received.

* _Viznutcracker, sweet!_
  * added a `Pitch` parameter, which sort-of controls the pitch or frequency of each equation, in a manner different to the `Speed` parameter - but still nothing like a 1V/octave VCO. Thanks to **tuukka,j** on MW for suggesting this and to **colb** (Colin) on MW for providing details of how this might be implemented.

* _Sequins_ (dual sequencer)
  * added as a new app.

* _Meta-Q_ (dual quantizer/scale sequencer)
  * added as a new app.

#### Changes between v1.0 and v1.1

* removal of some redundant code and unused libraries
* changes to the encoder direction setting when in calibration mode to accommodate the swap in GPIO pin assignment for the right encoder introduced in version 2c and later of the O&C PCBs - see [setting encoder directions](/O_C/calibration/#0-setting-encoder-directions) on the calibration wiki page.
 
* _Quantermain_
  * mappable input CV sources to control the built-in LFSR (Turing Machine) probability and range parameters have been added - yes, voltage-controlled Turing Machines!
  * mappable CV input sources to control the built-in Logistic Map R and range parameters have been added, so now the Logistic Map can also be voltage-controlled.
  * byte beat equations have been added as a third internal source for the quantiser, with a range of parameters that can be voltage controlled. Thus, rather than creating audio output using byte beats (which is still possible using the _Viznutcracker, sweet!_ app), uniquely, the Quantermain app can create four independent channels of quantised pitch voltage streams driven by clocked byte beat equations. We believe this is a completely novel application of byte beat equations, and one which produces surprisingly musically interesting results ([here is an example](https://soundcloud.com/bennelong-bicyclist/equitable-equations)).

* _Quadraturia_
  * a frequency range parameter for the quadrature LFOs has been added, with self-explanatory settings of "vslow", "slow", "med", "fast" and "vfast". The faster settings extend into audio range. Note that Quadraturia does not, and is not intended to, track 1V/octave.
  * output amplitude parameters for each channel have been removed (they weren't much use, it could be done in an external mixer anyway, and they wasted precious settings storage space).

* _Piqued_ 
  * voltage control over the Euclidean trigger filter parameters and the trigger delay time is now possible. Input CVs can be mapped to control the Euclidean trigger filter parameters: Eleng (Euclidean pattern length), Efill (Euclidean pattern fill, Eoffs (Euclidean pattern offset/rotation), or the trigger delay time (Delay).
  * added an new envelope type: Gate. This can be used when gate outputs are desired. The value rises immediately to maximum in the attack segment, and the value falls immediately to minimum in the decay and release segments. In other words, a gate pulse is output.

* _Viznutcracker, sweet!_
  * eight new byte beat equations have been added, bringing the total to 16. These new equations are also available as sources in the _Quantermain_ quantiser app (see above).
