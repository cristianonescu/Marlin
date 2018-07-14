
# Marlin 3D Printer Firmware for Anycubic I3 Mega
## with Original TFT display
### Based on work form Murdock (lesimprimantes3d.fr)
### Based on work from derhopp (https://github.com/derhopp) and Bartolomeus (Thingiverse)

MARLIN 2.0.x Anycubic I3 Mega V2 with original screen.

Firmware for the mega v2 (no ABL, dual Z and 8bits trigorilla card) which is a mix of the work of Murdock (lesimprimates3d.fr) for TFT32 MKS screen and the work of Derhopp from thingiverse.

This version allows you to switch to 2.0.x by keeping the original screen of the printer.

To install it, it's as usual, with arduino for compilation and then push everything on the printer. E.g. do the .hex file and send it with Octoprint (via the firmware plugin).

The values in the conf file for tuning or the extruder steps are normally good to start with. If needed, a small M502 and M500 to update the EEPROM can be required.

To go back to stock, just put the original Anycubic file (from their website).

Difference compared to anycubic official firmware:
* No start music
* No recovery after power failure
* Thermal runaway active
* Hotend fan can run at 12V (maybe put 85-90% instead of 100% for the fan otherwise it cool to much)
* Special menu from Derhopp active. New entry in the menu to put hotend in maintenance position
* More tests to do to see if everything is ok

************
New things on top of regular  marlin:

DerHopp made a special menu in the SD part. If you go to the print menu, you can select "Special Menu" at the top and press the round / arrow button to enter the menu.

The “genius” idea of the developer is to use the file selection screen on the SD to generate an additional menu.

It adds to the top of the list of files an entry that looks like a directory and is called "special menu". When we go in there there is a list of possible action. You already have some configured entries (read eeprom, save eeprom, auto tune ...). It compensates for the lack of customization of the lcd. And it's easy to add new ones if necessary as for lighting LEDs for example.

If you want to add / modify these entries, you have to edit the firmware and send it back to the trigorilla. Everything happens in the AnycubicTFT.cpp file:
in the AnycubicTFTClass :: Ls () section we add the menu entries (4 per page) of the <Auto Tune Hotend PID> style and then in the AnycubicTFTClass :: HandleSpecialMenu () section we define which command (s) will be started : M303 C8 S200.

************
M600 implementation (1.1.8) // NOT TESTED IN 2.0.X // DO NOT USE

Current parameters : Load/unload is configured to 500 (approximate length of the Bowden tube). Filament prime is configure to 50. This will create a bunch of filament on the back left corner before restarting print.

Print started from SD with on demand TFT M600:

When the print is on, you can press the "pause" button on the screen and then the gcode buffer will finish few moves, the hotend will park, filament will unload, printer will bip.
You can then put new filament and press "continue" button.
Filament is then loaded (hotend heating will restart first if required as it stop after a defined idle time) and when ok, the head will continue the print. You can remove filament oozing on the file before hotend start printing again.
This can be repeated as many time as you want.
"Pause failed" message can appears on screen but this is cosmetic only and cannot be changed.


Print started from usb on demand M600 from TFT screen:

When the print is on, you can press the "M600 pause" entry in the special menu and then the gcode buffer will finish few moves, the hotend will park, filament will unload, printer will bip.
You can then put new filament and press "M600 resume" entry in the special menu.
Filament is then loaded (hotend heating will restart first if required as it stop after a defined idle time) and when ok, the head will continue the print. You can remove filament oozing on the file before hotend start printing again.
This can be repeated as many time as you want.


Print started from usb on demand M600 from usb serial command (need more test to make sure M108 is taken in account every time):

When the print is on, you can send M600 and then the gcode buffer will finish few moves, the hotend will park, filament will unload, printer will bip.
You can then put new filament and you can press "M600 resume" entry in the special menu or press "Speed" entry in the TFT menu and then "OK".
Filament is then loaded (hotend heating will restart first if required as it stop after a defined idle time) and when ok, the head will continue the print. You can remove filament oozing on the file before hotend start printing again.
This can be repeated as many time as you want.

Print started from usb M600 in the gcode:

When the print is on, when M600 is seen, the hotend will park, filament will unload, printer will bip.
You can then put new filament and press "M600 resume" entry in the special menu.
Filament is then loaded (hotend heating will restart first if required as it stop after a defined idle time) and when ok, the head will continue the print. You can remove filament oozing on the file before hotend start printing again.
This can be repeated as many time as you want.


Print started from SD M600 in the gcode:

When the print is on, when M600 is seen, the hotend will park, filament will unload, printer will bip.
You can then put new filament and press "Speed" entry in the TFT menu and then "OK".
Filament is then loaded (hotend heating will restart first if required as it stop after a defined idle time) and when ok, the head will continue the print. You can remove filament oozing on the file before hotend start printing again.
This can be repeated as many time as you want.

Note that Filament sensor will trigger M600 and to resume, you should use "Speed" entry in the TFT menu and then "OK".

************

# FAQ

###### My special menu does not work :

In order to use the menu, a SD card must be in the printer. When choosing entry, when it turns red, you should validate your choice with the "rounded arrow" button

###### My special menu hang :

Please remove the Chinese folders/files from the SD card

###### My printer stop just after first layer :

As the fan is now capable to go to 100% when it start (generally after the first layer) then it is possible that the hotend temperature drops too much and beyond the thermal runaway configured in the firmware. Two options here : change slicer setting to move avoid 0->100% and have maybe second layer at 80 then third one to 90 and so on. Otherwise, you can as well change the firmware setting and compile it again.

###### My print quality does not look good :

You need to perform few optional operations to make sure the settings are accurate:

1. Reset the EEPROM settings (to start fresh with firmware values)

 Just do a M502 to restore factory firmware value and a M500 to save them.

 Send: M502 Recv: echo:Hardcoded Default Settings Loaded

 Send: M500 Recv: echo:Settings Stored (614 bytes; crc 3761)

2. Auto Tune PID

 PID Tuning: We start cold and we do a: M303 E0 S200 C8 U1

 We see the values found at the end of the test:

 Recv: PID Autotune finished!

 #define DEFAULT_Kp 14.23

 #define DEFAULT_Ki 1.03

 #define DEFAULT_Kd 49.32

 and we save with an M500

 (U1 directive allow to remove the need of manual update via a: M301 P14.23 I1.03 D49.32)

3. Change Step values for extruder if required

 We write down the current value of the steps with the command M503 and we look at the value found for the M92 behind the parameter E (92.6 by default on the i3)
 To adjust the extruder, it makes a mark on the filament from the extruder at 15 cm for example.

 Reset to zero the extrusion counter with a G92 E0
 Then the hotend is heated and the following command is used to push the filament by 10 cm: G1 E100 F 92

 Then we measure how much centimeters it remains between the mark and the extruder and we calculate the new value of step: Ex: 9.1 cm are taken instead of 10 so the value will be 92.6 * 100/91 = 102 (old value * 100 / number of cm taken).

 We send the new value in the printer: M92 E102

 We save the values: M500

4. Change the hotted fan speed.

 As the fan is now capable to go to 100% when it start (generally after the first layer) then it is possible that the hotend temperature drops too much and beyond the thermal runaway configured in the firmware.

 Two options here : change slicer setting to move avoid 0->100% and have maybe second layer at 80 then third one to 90 and so on. Otherwise, you can as well change the firmware setting and compile it again.

 This is in the configuration_adv file :

 * if ENABLED(THERMAL_PROTECTION_HOTENDS)
 * define THERMAL_PROTECTION_PERIOD 40        // Seconds
 * define THERMAL_PROTECTION_HYSTERESIS 4     // Degrees Celsius

 Please note that the official firmware has this setting "disable" which is a huge risk.

 Documentation state :

  * Thermal Protection provides additional protection to your printer from damage
  * and fire. Marlin always includes safe min and max temperature ranges which
  * protect against a broken or disconnected thermistor wire.

  * The issue: If a thermistor falls out, it will report the much lower
  * temperature of the air in the room, and the the firmware will keep
  * the heater on.

  * The solution: Once the temperature reaches the target, start observing.
  * If the temperature stays too far below the target (hysteresis) for too
  * long (period), the firmware will halt the machine as a safety precaution.

  * If you get false positives for "Thermal Runaway", increase
  * THERMAL_PROTECTION_HYSTERESIS and/or THERMAL_PROTECTION_PERIOD

5. Change the K value for linear advance.

 Value for K is set at 0. You can activate Linear advance but yu can have some issue with small segments/details.
 You can use the gcode generator on marlin website if you want to adjust the value to your printer/filament. (http://marlinfw.org/docs/features/lin_advance.html)
 Command to change it is M900 Kxx (where xx is what you found with the test)

***
***
***

Tutorial firmware update by Pierre Multi on Anycubic english forum:


Flashing Mega i3 with Octoprint

1. Add OctoPrint-FirmwareUpdater via plugin manager

2. AVRDUDE Installation

 AVRDUDE needs to be installed on the server where OctoPrint is running.

 Raspberry Pi

 sudo apt-get update

 sudo apt-get install avrdude

3. Setup FirmwareUpdater

 in Octoprint Settings / Firmware Updater / parameters

 Flash method : avrdude

 AVR MCU : ATmega2560

 Path to avrdude : /usr/bin/avrdude

 AVR Programmer Type : wiring

4. Save : you are ready to flash


# Marlin 3D Printer Firmware

[![Build Status](https://travis-ci.org/MarlinFirmware/Marlin.svg?branch=RCBugFix)](https://travis-ci.org/MarlinFirmware/Marlin)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/2224/badge.svg)](https://scan.coverity.com/projects/2224)

<img align="top" width=175 src="buildroot/share/pixmaps/logo/marlin-250.png" />

Additional documentation can be found at the [Marlin Home Page](http://marlinfw.org/).
Please test this firmware and let us know if it misbehaves in any way. Volunteers are standing by!

## Marlin 2.0 Bugfix Branch

__Not for production use. Use with caution!__

Marlin 2.0 takes this popular RepRap firmware to the next level with support for much faster 32-bit processor boards.

This branch is for patches to the latest 2.0.x release version. Periodically this branch will form the basis for the next minor 2.0.x release.

Download earlier versions of Marlin on the [Releases page](https://github.com/MarlinFirmware/Marlin/releases).

## Building Marlin 2.0

To build Marlin 2.0 you'll need [Arduino IDE 1.9](https://www.arduino.cc/en/main/software) or [PlatformIO](http://docs.platformio.org/en/latest/ide.html#platformio-ide). We've posted detailed instructions on how to [build Marlin 2.0 for ARM](http://marlinfw.org/docs/basics/install_arm.html).

## Hardware Abstraction Layer (HAL)

Marlin 2.0 adds a new abstraction layer so that Marlin can build and run on 32-bit boards while still retaining full 8-bit AVR compatibility. In this way, features can be enhanced for more powerful platforms while still supporting AVR, whereas splitting up the code would make it harder to maintain and keep everything in sync.

### Current HALs

  name|processor|speed|flash|sram|logic|fpu
  ----|---------|-----|-----|----|-----|---
  [Arduino AVR](https://www.arduino.cc/)|ATmega, ATTiny, etc.|16-20MHz|64-256k|2-8k|5V|no
  [Teensy++ 2.0](http://www.microchip.com/wwwproducts/en/AT90USB1286)|[AT90USB1286](http://www.microchip.com/wwwproducts/en/AT90USB1286)|16MHz|128k|8k|5V|no
  [Due](https://www.arduino.cc/en/Guide/ArduinoDue), [RAMPS-FD](http://www.reprap.org/wiki/RAMPS-FD), etc.|[SAM3X8E ARM-Cortex M3](http://www.microchip.com/wwwproducts/en/ATsam3x8e)|84MHz|512k|64+32k|3.3V|no
  [Re-ARM](https://www.kickstarter.com/projects/1245051645/re-arm-for-ramps-simple-32-bit-upgrade)|[LPC1768 ARM-Cortex M3](http://www.nxp.com/products/microcontrollers-and-processors/arm-based-processors-and-mcus/lpc-cortex-m-mcus/lpc1700-cortex-m3/512kb-flash-64kb-sram-ethernet-usb-lqfp100-package:LPC1768FBD100)|100MHz|512k|32+16+16k|3.3-5V|no
  [MKS SBASE](http://forums.reprap.org/read.php?13,499322)|LPC1768 ARM-Cortex M3|100MHz|512k|32+16+16k|3.3-5V|no
  [Azteeg X5 GT](https://www.panucatt.com/azteeg_X5_GT_reprap_3d_printer_controller_p/ax5gt.htm)|LPC1769 ARM-Cortex M3|120MHz|512k|32+16+16k|3.3-5V|no
  [Selena Compact](https://github.com/Ales2-k/Selena)|LPC1768 ARM-Cortex M3|100MHz|512k|32+16+16k|3.3-5V|no
  [Teensy 3.5](https://www.pjrc.com/store/teensy35.html)|ARM-Cortex M4|120MHz|512k|192k|3.3-5V|yes
  [Teensy 3.6](https://www.pjrc.com/store/teensy36.html)|ARM-Cortex M4|180MHz|1M|256k|3.3V|yes

### HALs in Development

  name|processor|speed|flash|sram|logic|fpu
  ----|---------|-----|-----|----|-----|---
  [STEVAL-3DP001V1](http://www.st.com/en/evaluation-tools/steval-3dp001v1.html)|[STM32F401VE Arm-Cortex M4](http://www.st.com/en/microcontrollers/stm32f401ve.html)|84MHz|512k|64+32k|3.3-5V|yes
  [Smoothieboard](http://reprap.org/wiki/Smoothieboard)|LPC1769 ARM-Cortex M3|120MHz|512k|64k|3.3-5V|no

## Submitting Patches

Proposed patches should be submitted as a Pull Request against the ([bugfix-2.0.x](https://github.com/MarlinFirmware/Marlin/tree/bugfix-2.0.x)) branch.

- This branch is for fixing bugs and integrating any new features for the duration of the Marlin 2.0.x life-cycle.
- Follow the [Coding Standards](http://marlinfw.org/docs/development/coding_standards.html) to gain points with the maintainers.
- Please submit your questions and concerns to the [Issue Queue](https://github.com/MarlinFirmware/Marlin/issues).

### [RepRap.org Wiki Page](http://reprap.org/wiki/Marlin)

## Credits

The current Marlin dev team consists of:
 - Roxanne Neufeld [[@Roxy-3D](https://github.com/Roxy-3D)] - English
 - Scott Lahteine [[@thinkyhead](https://github.com/thinkyhead)] - English
 - Bob Kuhn [[@Bob-the-Kuhn](https://github.com/Bob-the-Kuhn)] - English
 - Chris Pepper [[@p3p](https://github.com/p3p)] - English
 - João Brazio [[@jbrazio](https://github.com/jbrazio)] - Portuguese, English

## License

Marlin is published under the [GPL license](/LICENSE) because we believe in open development. The GPL comes with both rights and obligations. Whether you use Marlin firmware as the driver for your open or closed-source product, you must keep Marlin open, and you must provide your compatible Marlin source code to end users upon request. The most straightforward way to comply with the Marlin license is to make a fork of Marlin on Github, perform your modifications, and direct users to your modified fork.

While we can't prevent the use of this code in products (3D printers, CNC, etc.) that are closed source or crippled by a patent, we would prefer that you choose another firmware or, better yet, make your own.
