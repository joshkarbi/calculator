# smart-calculator
A calculator that also displays information about battery power remaining, ambient light, and temperature.

Built for the Intel DE-10 Standard Development Board.

# Project Structure
src/ contains "production version" code, which reads input from a 4x4 keypad array connected to GPIO of the DE-10, as well as from a battery supply level comparator circuit.

src-demo/ contains similar code, but uses the board's switches and keys to simulate input from the keypad.

images/ contains design files and demo images.

# Configuring CMake for Building
Note: 'ccmake .' will bring up a CMake configuration window. Hit the "c" key, then "q" to quit.
Refer to cmake.org for installing instructions.
```bash
cd src/
ccmake .
```
Then run (on UNIX):
```bash
ccmake -G "Unix Makefiles"
```

# Building
Note: tinyexpr.c and tinyexpr.h from https://github.com/codeplea/tinyexpr will need to first be downloaded into src/utils/.
On Intel FPGA Monitor Program: May need to add gcc flag "-lm".
```bash
cd src/
make
```
