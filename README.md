# SmartCalculator
A calculator that also displays information about battery power remaining, ambient light, and temperature.

Being built to run on the Altera DE-10 Standard Development Board.

# Configuring CMake for Building
After ccmake . hit the "c" key, then "q" to quit.
```bash
cd src/
ccmake .
```
Then run (on UNIX):
```bash
ccmake -G "Unix Makefiles"
```

# Building
```bash
cd src/
make
```
