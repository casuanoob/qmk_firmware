# My keyboard layout for the [Charybdis Nano](https://https://bastardkb.com/charybdis-nano/)

This keymap reuses the "split34" layout defined in
[`casua-dev`](../../../../../../users/casuanoob/README.md).

## WIP Charybdis-EC11 Encoder breakout config and layout

- [x] Encoder rotation working
- [x] Encoder button press working
- [x] Fixed trackball issue
- [x] LEDs working

Note that this configuration is specific to the Blackpill - for other controllers a new `#define ENCODERS_PAD_A {pin}`, `#define ENCODERS_PAD_B {pin}`, `#define ENCODERS_PAD_A_RIGHT {pin}`, and `#define ENCODERS_PAD_B_RIGHT {pin}` will need to be set depending on how the encoder is connected.
If connecting to the trackball header on the shield, the encoder pads must be defined to unused pins on the trackball half, otherwise the trackball will stop working.

Encoder button press has been wired to the thumb cluster matrix, replacing the missing thumb key.

There are an optional 12 LEDs on the breakout. As the WS2812 driver requires the data line to be connected in a single chain and the Charybdis thumbs do not have a DOUT header, the data line connects from Shield -> Plate PCB -> Encoder breakout -> Thumbs PCB instead of the usual order. 

The LED index in [`3x5.c`](../../3x5.c) has been updated to reflect the changes.

In this configuration:
- VCC connected to trackball header
- GND connected to trackball header
- R1/pad A connected to MISO
- R2/pad B connected to MOSI
- DIN connected to DO on Plate PCB
- DOUT connected to DIN on Thumbs PCB
- BTN connected to R4
- Col connected to C5