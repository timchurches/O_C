---
title: custom scales
layout: default
---

adding or modifying existing scales is easy and doesn't require programming skills. it boils down to adding or editing the scale definitions, which are basically just ordered lists of numbers from `0 - 1536`, as described below.

- the **preset** scales are defined in `braids_quantizer_scales.h`, with their corresponding names in `OC_scales.cpp`. 

- for example, the **Phrygian** scale looks like this (see `braids_quantizer_scales.h`):

 ```
  // Phrygian 
   { 12 << 7, 7, { 0, 128, 384, 640, 896, 1024, 1280} }
 ```

- technically, a scale is a simple struct (defined in `braids_quantizer.h`), consisting of three members: `span`, `num_notes`, and `notes[16]`:

    ```
    struct Scale {
      int16_t span;
      size_t num_notes;
      int16_t notes[16];
    };
    ```

- where 
  - `span` is the scale **span**, namely `12 << 7` (= `1536 `= `1.0V` = `1 octave` = `1200cents`), 
  - `num_notes` the **number of notes** per scale, and 
  - `notes[16]` is an array containing the actual note values within that span, with a maximum of 16 notes per scale (and a minimum of 4).

- in other words, in terms of the preset scales, each octave has a **resolution** of `1536` steps, each step corresponding to `1/128th` of a semitone (or `0.78125` cents, or `0.65mV`). Conversely, `1 cent` translates to `1.28` steps, `1 semitone` to `128` steps. for converting ratios, use this formula: `1536 * Log(ratio)/Log(2)` (further [reading](http://www.tonalsoft.com/enc/number/7mu.aspx)).

- for **12-TET** scales, the note values thus will be multiples of `span` divided by **12**:

   `span / 12` = `1536 / 12` = `128` (= `83.33mV` = `1 semitone` = `100 cents`). 

- Or taking the **chromatic** scale as an example: in this case, `span = 1536`, `num_notes = 12`, and `notes` is an array consisting of 12 elements at semitone intervals from `0 - 1408`:

 ```
  // Semitones
  { 12 << 7, 12, { 0, 128, 256, 384, 512, 640, 768, 896, 1024, 1152, 1280, 1408} }
 ```

-  correspondingly, scales with fewer notes will have the **same** `span` but fewer elements, e.g. **Pentatonic minor** with only 5 notes:

 ```
// Pentatonic minor 
  { 12 << 7, 5, { 0, 384, 640, 896, 1280} }
 ```

- where: 
  - `0 = 0 * 128 = 0 * 0.78125 cents = 0 cents`, 
  - `384 = 3 * 128 = 384 * 0.78125 cents = 300 cents` (minor third), 
  - `640 = 5 * 128 = 640 * 0.78125 cents = 500 cents` (fourth), 
  - `896 = 7 * 128 = 896 * 0.78125 cents = 700 cents` (fifth), and 
  - `1280 = 10 * 128 = 1280 * 0.78125 cents = 1000 cents` (minor seventh)).  

- **non-12-TET** scales/intonations work much the same way, except the intervals won't be multiples of `128`; for example:

 ```
// bairagi 
  { 12 << 7, 5, { 0, 115, 637, 899, 1275} }
 ```

- where `span = 12 << 7 = 1536` (as before), `num_notes = 5`, and 

  - `notes[0] = 0`, 
  - `notes[1] = 115 =~ 90 cents = 115 * 0.78125 cents`, 
  - `notes[2] = 637 =~ 498 cents = 637 * 0.78125 cents`, and so on.

- the displayed names (short and long version) are stored in **two** arrays: `const char* const scale_names[]` and `const char* const scale_names_short[]`, with their names given at the index corresponding to the actual scale definition in `const Scale scales[]`.

- to add your own scale, you'll simply have to:

  - 1. add the suitable **scale definition** to `const Scale scales[]`, as well as 
  - 2. add (at the corresponding array position) the short and long versions of the **scale name** to `scale_names[]` and `scale_names_short[]`, respectively. 
  - 3. re-compile as per method B [here](/O_C/firmware/#method-b-compiling-the-firmware).

