# Simple USB Target Code for Pi Pico
This repository contains a very simple Pi Pico project that works as a demo target for the AnyOperate client software.

The code exposes a variable called **duty** that can be controlled from the AnyOperate mobile app for Android.

By changing the value from 0 to 100, the green LED on Pi Pico boards will blink at that duty cycle.

# Using the Pre-built Firmware

A pre-built .uf2 binary is available in the build-pico-Release folder. Hold down the BOOT button on the Pi Pico, then insert the USB cable to the PC, and then release the BOOT button. A drive letter should appear on the PC. Drag-and-drop the .uf2 file on the drive letter, and the Pi Pico firmware should be uploaded within seconds, and the code will immediately begin execution.

The code blinks the green LED at 50% duty cycle by default. Disconnect the Pi Pico from the PC, and attach it to a mobile phone running AnyOperate. Select USB in the AnyOperate app, then go to Configure, and you should see a duty cycle value there to adjust and see the effect.

# Building the Code
You'll need your PC set up to with the Pi Pico RP2040 C/C++ SDK installed, and the ARM GNU Toolchain. Inspect (and most likely adjust) the build.ps1 file if you wish to build on Windows using PowerShell.
