# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.12.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.12.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src"

# Include any dependencies generated for this target.
include CMakeFiles/TestCalculatorMath.exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TestCalculatorMath.exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestCalculatorMath.exe.dir/flags.make

CMakeFiles/TestCalculatorMath.exe.dir/tests/TestCalculatorMath.c.o: CMakeFiles/TestCalculatorMath.exe.dir/flags.make
CMakeFiles/TestCalculatorMath.exe.dir/tests/TestCalculatorMath.c.o: tests/TestCalculatorMath.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TestCalculatorMath.exe.dir/tests/TestCalculatorMath.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TestCalculatorMath.exe.dir/tests/TestCalculatorMath.c.o   -c "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src/tests/TestCalculatorMath.c"

CMakeFiles/TestCalculatorMath.exe.dir/tests/TestCalculatorMath.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TestCalculatorMath.exe.dir/tests/TestCalculatorMath.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src/tests/TestCalculatorMath.c" > CMakeFiles/TestCalculatorMath.exe.dir/tests/TestCalculatorMath.c.i

CMakeFiles/TestCalculatorMath.exe.dir/tests/TestCalculatorMath.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TestCalculatorMath.exe.dir/tests/TestCalculatorMath.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src/tests/TestCalculatorMath.c" -o CMakeFiles/TestCalculatorMath.exe.dir/tests/TestCalculatorMath.c.s

CMakeFiles/TestCalculatorMath.exe.dir/utils/tinyexpr.c.o: CMakeFiles/TestCalculatorMath.exe.dir/flags.make
CMakeFiles/TestCalculatorMath.exe.dir/utils/tinyexpr.c.o: utils/tinyexpr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TestCalculatorMath.exe.dir/utils/tinyexpr.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TestCalculatorMath.exe.dir/utils/tinyexpr.c.o   -c "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src/utils/tinyexpr.c"

CMakeFiles/TestCalculatorMath.exe.dir/utils/tinyexpr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TestCalculatorMath.exe.dir/utils/tinyexpr.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src/utils/tinyexpr.c" > CMakeFiles/TestCalculatorMath.exe.dir/utils/tinyexpr.c.i

CMakeFiles/TestCalculatorMath.exe.dir/utils/tinyexpr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TestCalculatorMath.exe.dir/utils/tinyexpr.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src/utils/tinyexpr.c" -o CMakeFiles/TestCalculatorMath.exe.dir/utils/tinyexpr.c.s

# Object files for target TestCalculatorMath.exe
TestCalculatorMath_exe_OBJECTS = \
"CMakeFiles/TestCalculatorMath.exe.dir/tests/TestCalculatorMath.c.o" \
"CMakeFiles/TestCalculatorMath.exe.dir/utils/tinyexpr.c.o"

# External object files for target TestCalculatorMath.exe
TestCalculatorMath_exe_EXTERNAL_OBJECTS =

TestCalculatorMath.exe: CMakeFiles/TestCalculatorMath.exe.dir/tests/TestCalculatorMath.c.o
TestCalculatorMath.exe: CMakeFiles/TestCalculatorMath.exe.dir/utils/tinyexpr.c.o
TestCalculatorMath.exe: CMakeFiles/TestCalculatorMath.exe.dir/build.make
TestCalculatorMath.exe: CMakeFiles/TestCalculatorMath.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable TestCalculatorMath.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestCalculatorMath.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TestCalculatorMath.exe.dir/build: TestCalculatorMath.exe

.PHONY : CMakeFiles/TestCalculatorMath.exe.dir/build

CMakeFiles/TestCalculatorMath.exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestCalculatorMath.exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestCalculatorMath.exe.dir/clean

CMakeFiles/TestCalculatorMath.exe.dir/depend:
	cd "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src" "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src" "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src" "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src" "/Users/joshuakarbi/Desktop/2018-2019/School/ECE 3375/SmartCalculator/src/CMakeFiles/TestCalculatorMath.exe.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/TestCalculatorMath.exe.dir/depend

