---
title: Hardware CHANGELOG
---

# PCB versions

## NB: prior to version `2.c`, the input stage consisted of a TL074 (+BAT54s), _not_ a MCP6004. other than that, the differences between recent versions are _very_ minor. see [here](https://github.com/mxmxmx/O_C/wiki/BOM_legacy) for the legacy BOM.


### rev 2.e (07/2016)

- colour: red, labelled `rev 2.e`
- silkscreen corrections (75k, 560p)
- trimpots removed
- supported by current firmware

### rev 2.d (04/2016) 

- colour: red, labelled `rev 2.d`
- make everything 0805 -> move 10n caps into feedback loop 
- add CC-BY-SA licence
- supported by current firmware

### rev 2.c (12/2015) 

- colour: yellow, labelled `rev 2.c`
- move mounting hole -> improve mechanical stability
- ditch pull-up resistors (for switches, triggers)
- ditch 78L33 regulator, use onboard 3v3 instead (3v3_D)
- add 10k pull-up for OLED CS signal.
- **replace TL074/bat54s with MCP6004**
- supported by current firmware

### rev 2.b (07/2015)

- colour: yellow, labelled `rev.2`
- ditch the alternative (adafruit) OLED header
- ditch alt. headers for CV signals
- add holes (underneath the jacks)
- supported by current firmware

### rev 2.a (05/2015)

- colour: yellow, labelled `rev.2`
- use LM1117, not 7805 regulator
- use LM4040 voltage reference, not 79L05 regulator
- simplify output stage: **replace** offset trimpot with divider
- simplify output stage: 4x single inverting op-amps
- supported by current firmware.

### rev 1 (08/2014)

- colour: yellow, labelled `rev.1`
- replace precision resistors with rheostats.
- needs **modification** of the output stage to work with the current firmware.

### rev 0 (06/2014) 
- colour: green, labelled `4xCV`
- unpublished
