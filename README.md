# SmartCalculator
A calculator that also displays information about battery power remaining, ambient light, and temperature.

Being built to run on the Altera DE-10 Standard Development Board.

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
On Intel FPGA Monitor Program: Add gcc flag "-lm".
```bash
cd src/
make
```

![alt text](https://github.com/joshuakarbi/SmartCalculator/blob/master/images/demo1.JPG)
