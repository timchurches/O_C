---
title: Licensing
layout: default
---

The following licensing provisions apply to the Ornament + Crime (O+C) hardware design, the Ornaments + Crimes firmware and its source code bundle (repository), and to the associated documentation for both the hardware and the firmware and its source code.

## PCB files

The Gerber files for the various versions of the O+C PCBs are copyright M. Stadler and are released under the [Creative Commons Attribution-ShareAlike 4.0 International](https://creativecommons.org/licenses/by-sa/4.0/) (CC BY-SA 4.0) license. 

Anyone wishing to build O + C modules using PCBs produced from the PCB files is welcome to do so. If you are making copies of the PCBs for personal use or on behalf of a small group of people, there are no other considerations - please proceed. If you are making copies of the PCBs for commercial sale or as part of a large group-buy, please consult the _Considerations for licensees_ section of [this Creative Commons document](https://wiki.creativecommons.org/wiki/Considerations_for_licensors_and_licensees#Considerations_for_licensees) and note the request to comply with non-binding licensor preferences. For the Ornament + Crime PCB files, the licensor (M. Stadler) requests that anyone intending to undertake a large-scale (say, 20 or more) group-buy purchase of O+C PCBs or anyone intending to offer them for sale on a commercial basis informs him of such intentions via email.

## Ornaments + Crimes (the firmware bundle for the Ornament + Crime hardware module)

The Ornaments + Crimes firmware bundle comprises all the source code contained in the O_C GitHub repositories at the following URLs, and any clones or copies of those repositories: 

* https://github.com/mxmxmx/O_C/
* https://github.com/patrickdowling/O_C/
* https://github.com/timchurches/O_C/

Most of the individual source code files in the O_C firmware bundle (repository) have MIT license headers, and the copyright holders for them are shown in that header. A few files lack such headers, in which case, the files are copyright M.Stadler and P. Dowling, 2015, 2016, and should be considered to have an MIT license attached to them.

Some of the source code files have been written by third parties, and the relevant copyrights are shown in the license headers in those files. In particular, quite a few of the files are copyright O. Gillet 2013-2015, or are copyright P.  Stoffregen (PJRC.COM LLC) 2012-2016, and have been released by their authors under an MIT license which permits their re-use and adaption as part of the O_C firmware bundle.

However, at least one source code file used in the O_C firmware bundle is licensed under the GNU Public License v3.0 (GPL3) - see [drivers/SH1106_128x64_driver.cpp](https://github.com/mxmxmx/O_C/blob/master/software/o_c_REV/drivers/SH1106_128x64_driver.cpp), because it is derived from code that was itself released under the GPLv3 license. Due to the "copyleft" provisions of the GPL3 license, the necessary inclusion of this file in the O_C firmware bundle means that **all** the source code contained in the O_C firmware bundle (i.e. in the O_C repositories), and any binary files derived from it, are all implicitly subject to the provisions of the GPLv3 license. Note that this only applies to the source code contained in the O_C bundle (and copies and clones thereof) used to create the O+C firmware binaries. Copies of third-party code obtained from their original third-party sources (e.g. source code from Olivier Gillet's GitHub repository for the Mutable Instruments modules) are not subject to the GPLv3 provisions which apply to that source code as used and adapted in the O_C bundle.

### Implications of the MIT and GPLv3 licenses

For DIY makers and end users of the O&C module, these licensing arrangements do not impose any additional burden or duties on you: you are free to build the module, use it, modify the firmware, and sell modules to others. If you sell modules to others (which means you are providing a copy of the firmware), please make sure the buyer is aware of this documentation here on GitHub - that will be sufficient to satisfy the following clause in the MIT license:

> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

For third-party module manufacturers wishing to re-use O+C code in your products, the licenses permit you to do so, but they also impose some additional duties on you:
* the GPLv3 license requires you to release, also under the GPLv3 or some other compatible open-source license, all the source code for any module in which you have used GPLv3-licensed O+C code
* the MIT license requires you to include the various copyright notices in the O+C source code headers and the MIT license permission notice in all copies or substantial portions of "the Software". The "Software" includes any binaries compiled from code which includes any O+C source code i.e. the firmware flashed to module MPUs. Therefore, these copyright assertions and permission notices must be included in any manual or other documentation for your module, including printed documentation provided with the module. 

If you feel that you cannot comply with these licensing requirements, then please do not re-use O+C code in your products.

## Documentation

The O+C build guides and the firmware manual are all licensed under the [Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)](https://creativecommons.org/licenses/by-nc-sa/4.0/) license. Please observe the provisions of this license if you copy or re-use the documentation.
