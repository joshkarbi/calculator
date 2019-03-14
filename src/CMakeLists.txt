

cmake_minimum_required (VERSION 2.6)
project (IntelliCalc)

add_executable(IntelliCalc.exe main.c utils/CalculatorMath.c)
add_executable(TestCalculatorMath.exe tests/TestCalculatorMath.c utils/CalculatorMath.c)