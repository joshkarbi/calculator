
echo "TestCalculatorMath"
gcc tests/TestCalculatorMath.c -std=c89 -o TestCalculatorMath.exe utils/CalculatorMath.c -Itests -Iutils