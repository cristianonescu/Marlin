
# Marlin 3D Printer Firmware for Anycubic I3 Mega
## with Original TFT display
### Based on work form Murdock (lesimprimantes3d.fr)
### Based on work from derhopp (https://github.com/derhopp) and Bartolomeus (Thingiverse)

## Bugfix Branch

__Not for production use. Use with caution!__

MARLIN 1.1.8 Anycubic I3 Mega V2 with original screen.

Firmware for the mega v2 (no ABL, dual Z and 8bits trigorilla card) which is a mix of the work of Murdock (lesimprimates3d.fr) for TFT32 MKS screen and the work of Derhopp from thingiverse.

This version allows you to switch to 1.1.8 by keeping the original screen of the printer.

To install it, it's as usual, with arduino for compilation and then push everything on the printer. E.g. do the .hex file and send it with Octoprint (via the firmware plugin).

The values in the conf file for tuning or the extruder steps are normally good to start with. If needed, a small M502 and M500 to update the EEPROM can be required.

To go back to stock, just put the original Anycubic file (from their website).

Difference compared to anycubic official firmware:
* No start music
* No recovery after power failure
* Thermal runaway active
* ABL linear active (Touch mi setup)
* Hotend limitation at 250°. (can be too small for petg and ABS but good limit for V5 hotend)
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
 Then the hotend is heated and the following command is used to push the filament by 10 cm: G1 E10 F 92

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


***
POWER RECOVERY:

You enable the power outage function with G6 gcode

If power outage occur, You should be able to start print back to latest position with a G8 gcode (or via special menu) when you print form SD card (even when printing from SD card with octoprint)

If you print via octoprint (not from SD) or from other software via USB, you can get latest information (G7 gcode) about the print such as : nozzle XYZ position, Hotend and Bed temperature, few Gcode command that where in queue. This should provide enough info to go to the slicer and start the print again from the right Z height....

I'll do some more tests and will integrate that to the firmware source/.hex on the page.

Example :

Recv : G6 POWER LOSS RECOVERY ACTIVATED

----
Recv: POWER LOSS RECOVERY LAUNCHED

Recv: Saving job_recovery_info

Recv: valid_head:1 valid_foot:1

Recv: current_position: -5.00: 0.00: 5.00: 0.00

Recv: feedrate: 3.33

Recv: target_temperature: 22

Recv: fanSpeeds: 0

Recv: leveling: 0 fade: 0

Recv: target_temperature_bed: 22

Recv: cmd_queue_index_r: 1

Recv: commands_in_queue: 4

Recv: > M27

Recv: > G1 X150 F200

Recv: > G1 Y150 F200

Recv: > G1 X-150 F200

Recv: sd_filename: /TESTING.GCO

Recv: sdpos: 367

Recv: print_job_elapsed: 14000

Recv: Writing to file: bin

----

Recv: G8 POWER LOSS RECOVERY FROM SD

Recv: Init job recovery info. Size: 568

Recv: echo:enqueueing "M420 S0"

Recv: echo:enqueueing "M190 S22"

Recv: echo:enqueueing "M109 S22"

Recv: valid_head:1 valid_foot:1

Recv: current_position: -5.00: 0.00: 5.00: 0.00

Recv: feedrate: 3.33

Recv: target_temperature: 22

Recv: fanSpeeds: 0

Recv: leveling: 0 fade: 0

Recv: target_temperature_bed: 22

Recv: cmd_queue_index_r: 1

Recv: commands_in_queue: 0

Recv: > M420 S0 Z0

Recv: > G92.0 Z0

Recv: > G1 Z2

Recv: > G28 X Y

Recv: > M420 S0 Z

Recv: > G92.0 Z7.000 E0.000

Recv: > M117 Continuing...

Recv: > G1 X150 F200

Recv: > G1 Y150 F200

Recv: > G1 X-150 F200

Recv: > M27

Recv: sd_filename: /TESTING.GCO

Recv: sdpos: 367

Recv: print_job_elapsed: 14000

Recv: echo:Now fresh file: /TESTING.GCO

Recv: File opened: TESTING.GCO Size: 944

Send: M27

Recv: File selected

Recv: ok

Recv: echo:enqueueing "G28 X Y"

Recv: echo:Bed Leveling Off

Recv: echo:Fade Height Off

Recv: TFT Serial Debug: Bed is heating... J08

Recv: TFT Serial Debug: Bed heating is done... J09

Recv: TFT Serial Debug: Nozzle is heating... J06

Recv: TFT Serial Debug: Nozzle heating is done... J07

...

***
***
***

# Marlin 3D Printer Firmware

[![Build Status](https://travis-ci.org/MarlinFirmware/Marlin.svg?branch=RCBugFix)](https://travis-ci.org/MarlinFirmware/Marlin)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/2224/badge.svg)](https://scan.coverity.com/projects/2224)

<img align="top" width=175 src="buildroot/share/pixmaps/logo/marlin-250.png" />

Additional documentation can be found at the [Marlin Home Page](http://marlinfw.org/).
Please test this firmware and let us know if it misbehaves in any way. Volunteers are standing by!

## Bugfix Branch

__Not for production use. Use with caution!__

This branch is used to accumulate patches to the latest 1.1.x release version. Periodically this branch will form the basis for the next minor 1.1.x release.

Download earlier versions of Marlin on the [Releases page](https://github.com/MarlinFirmware/Marlin/releases). (The latest tagged release of Marlin is version 1.1.7.)

## Recent Changes
- Internally always use native machine space
- Initial UBL LCD Menu
- New optimized G-code parser singleton
- Initial `M3`/`M4`/`M5` Spindle and Laser support
- Added `M421 Q` to offset a mesh point
- Refinements to `G26` and `G33`
- Added `M80 S` to query the power state
- "Cancel Print" now shuts off heaters
- Added `EXTRAPOLATE_BEYOND_GRID` option for mesh-based leveling

## Submitting Patches

Proposed patches should be submitted as a Pull Request against this branch ([bugfix-1.1.x](https://github.com/MarlinFirmware/Marlin/tree/bugfix-1.1.x)).

- This branch is for fixing bugs and integrating any new features for the duration of the Marlin 1.1.x life-cycle. We've opted for a simplified branch structure while we work on the maintainability and encapsulation of code modules. Version 2.0 and beyond should improve on separation of bug fixes and cutting-edge development.
- Follow the proper coding style to gain points with the maintainers. See our [Coding Standards](http://marlinfw.org/docs/development/coding_standards.html) page for more information.
- Please submit your questions and concerns to the [Issue Queue](https://github.com/MarlinFirmware/Marlin/issues). The "naive" question is often the one we forget to ask.

### [RepRap.org Wiki Page](http://reprap.org/wiki/Marlin)

## Credits

The current Marlin dev team consists of:
 - Roxanne Neufeld [[@Roxy-3D](https://github.com/Roxy-3D)]
 - Scott Lahteine [[@thinkyhead](https://github.com/thinkyhead)]
 - Bob Kuhn [[@Bob-the-Kuhn](https://github.com/Bob-the-Kuhn)]

Notable contributors include:
 - Alberto Cotronei [[@MagoKimbra](https://github.com/MagoKimbra)]
 - Andreas Hardtung [[@AnHardt](https://github.com/AnHardt)]
 - Bernhard Kubicek [[@bkubicek](https://github.com/bkubicek)]
 - Bob Cousins [[@bobc](https://github.com/bobc)]
 - Chris Palmer [[@nophead](https://github.com/nophead)]
 - David Braam [[@daid](https://github.com/daid)]
 - Edward Patel [[@epatel](https://github.com/epatel)]
 - Erik van der Zalm [[@ErikZalm](https://github.com/ErikZalm)]
 - Ernesto Martinez [[@emartinez167](https://github.com/emartinez167)]
 - F. Malpartida [[@fmalpartida](https://github.com/fmalpartida)]
 - Jochen Groppe [[@CONSULitAS](https://github.com/CONSULitAS)]
 - João Brazio [[@jbrazio](https://github.com/jbrazio)]
 - Kai [[@Kaibob2](https://github.com/Kaibob2)]
 - Luc Van Daele[[@LVD-AC](https://github.com/LVD-AC)]
 - Nico Tonnhofer [[@Wurstnase](https://github.com/Wurstnase)]
 - Petr Zahradnik [[@clexpert](https://github.com/clexpert)]
 - Thomas Moore [[@tcm0116](https://github.com/tcm0116)]
 - [[@alexxy](https://github.com/alexxy)]
 - [[@android444](https://github.com/android444)]
 - [[@benlye](https://github.com/benlye)]
 - [[@bgort](https://github.com/bgort)]
 - [[@Grogyan](https://github.com/Grogyan)]
 - [[@marcio-ao](https://github.com/marcio-ao)]
 - [[@maverikou](https://github.com/maverikou)]
 - [[@oysteinkrog](https://github.com/oysteinkrog)]
 - [[@p3p](https://github.com/p3p)]
 - [[@paclema](https://github.com/paclema)]
 - [[@paulusjacobus](https://github.com/paulusjacobus)]
 - [[@psavva](https://github.com/psavva)]
 - [[@Tannoo](https://github.com/Tannoo)]
 - [[@teemuatlut](https://github.com/teemuatlut)]
 - ...and many others

## License

Marlin is published under the [GPL license](/LICENSE) because we believe in open development. The GPL comes with both rights and obligations. Whether you use Marlin firmware as the driver for your open or closed-source product, you must keep Marlin open, and you must provide your compatible Marlin source code to end users upon request. The most straightforward way to comply with the Marlin license is to make a fork of Marlin on Github, perform your modifications, and direct users to your modified fork.

While we can't prevent the use of this code in products (3D printers, CNC, etc.) that are closed source or crippled by a patent, we would prefer that you choose another firmware or, better yet, make your own.
