Ornaments & Crimes is free, open-source software (firmware) for the Ornament + Crime module. The licenses under which the software is released permit anyone to freely install and use the firmware on copies of the module, to modify it, and to provide copies to others. Third-party module manufacturers who re-use portions of the O+C software in their modules or devices should ensure that they meet the obligations imposed by the licenses under which the O+C source code is released - details are [here](/O_C/licensing/).

##There are two ways of getting the firmware onto your module:

- [Method A](#method-a-uploading-the-hex-file): upload a pre-compiled HEX file. this is easy and quick. or
- [Method B](#method-b-compiling-the-firmware): install the Arduino IDE and the Teensyduino add-on and compile the code yourself. this option is required if you wanted to hack the code, etc.
- either way, you'll need: a **micro-usb cable** (make sure this isn't for charging only, but data transfer).
- NB: the following steps assume that you have cut the **usb trace**. see [here](/O_C/build-it/#finally-prepare-the-teensy).

# method A: uploading the HEX file

### step 1): install the Teensy Loader program

- the Teensy Loader is available at https://www.pjrc.com/teensy/loader.html

### step 2): download the binary HEX file

- download the latest released version of the Ornaments and Crimes firmware image file (.hex) from https://github.com/mxmxmx/O_C/releases

### step 3): open the HEX file in the Teensy Loader

- open the HEX file in the Teensy Loader application
- make sure a USB cable is connected to the Teensy, and that the O+C module is powered up
- press the program push switch on the Teensy board (on the back of the O+C module)
- click the Program icon, or choose Program from the Operation menu in Teensy Loader
  - you should briefly see a progress bar as the firmware is uploaded
- click the reboot icon or choose Operation | Reboot
- your O+C should now run the updated firmware (resp. come to life, if newly built)
- if this is a **newly built** module, proceed to [Calibration](/O_C/calibration/) (just updating the firmware doesn't require re-calibration)

# method B: compiling the firmware:

### step 1): get the IDE

- if you don’t have it already, you need to install the [arduino IDE](https://www.arduino.cc/en/Main/Software) as well as the [teensyduino add-on](https://www.pjrc.com/teensy/td_download.html). Make sure you have/install a **compatible** version: at the time of writing, that's arduino 1.6.8 through 1.8.1 and teensyduino 1.35, respectively. more recent versions (ideally) should work, too, but there's no guarantee they do. (we try to keep things in sync with up-to-date releases, but the arduino IDE is a moving target ...)

- with an eye to **step #2** below, when prompted during teensyduino installation procedure, choose to install the optional teensy **library** called **ADC**.

### step 2): install ADC library

- if you don't have it already (see above - it comes with teensyduino), you have to install this additional [library](https://github.com/pedvide/ADC). 

- an easy way to do so is by downloading the .zip file from github, then add it via the "library manager": 

  `Sketch` > `Include Library` > `Add .ZIP Library`

- or clone the repo (with git) and put the folder in your libraries folder.

### step 3): clone or download the firmware source code repository to your computer
- clone from https://github.com/mxmxmx/O_C or download the [.zip](https://github.com/mxmxmx/O_C/archive/master.zip) file.
- use the master branch (which is the default) - the master branch contains the latest "production" released code
- the develop and other branches contain bleeding-edge code which may or may not contain bugs
  
### step 4): compile

- once the libraries and the source code for Ornaments and Crimes are in place, you should be able to **compile** the Ornaments & Crimes firmware. Open the file called **o_c_REV.ino**. now make sure you:

      - 1) select teensy 3.2/3.1 in `Tools>Board`. and 
      - 2) select '120MHz optimzed (overclock)' in `Tools>CPU Speed`. and
      - 3) select 'Faster' (= o2) in `Tools>Optimize` (teensyduino 1.34 and later)

- things should look somewhat like this:

  ![pix](https://c2.staticflickr.com/2/1618/26563326745_d2d662877a_o.png)

- compile. and download to your board (since you've cut the usb trace, the module needs to be powered from your eurorack PSU): the display should come to life now.

-  if this is a **newly built** module, proceed to [Calibration](/O_C/calibration/) (just updating the firmware doesn't require re-calibration).
