# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /home/karaya_12/Program/clion-2018.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/karaya_12/Program/clion-2018.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/karaya_12/Coding/Operating System Concepts/Assignment III/Scheduling_Algorithm"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/karaya_12/Coding/Operating System Concepts/Assignment III/Scheduling_Algorithm/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Scheduling_Algorithm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Scheduling_Algorithm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Scheduling_Algorithm.dir/flags.make

CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o: CMakeFiles/Scheduling_Algorithm.dir/flags.make
CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/karaya_12/Coding/Operating System Concepts/Assignment III/Scheduling_Algorithm/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o -c "/home/karaya_12/Coding/Operating System Concepts/Assignment III/Scheduling_Algorithm/main.cpp"

CMakeFiles/Scheduling_Algorithm.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Scheduling_Algorithm.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/karaya_12/Coding/Operating System Concepts/Assignment III/Scheduling_Algorithm/main.cpp" > CMakeFiles/Scheduling_Algorithm.dir/main.cpp.i

CMakeFiles/Scheduling_Algorithm.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Scheduling_Algorithm.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/karaya_12/Coding/Operating System Concepts/Assignment III/Scheduling_Algorithm/main.cpp" -o CMakeFiles/Scheduling_Algorithm.dir/main.cpp.s

CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o.requires

CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o.provides: CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Scheduling_Algorithm.dir/build.make CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o.provides

CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o.provides.build: CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o


# Object files for target Scheduling_Algorithm
Scheduling_Algorithm_OBJECTS = \
"CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o"

# External object files for target Scheduling_Algorithm
Scheduling_Algorithm_EXTERNAL_OBJECTS =

Scheduling_Algorithm: CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o
Scheduling_Algorithm: CMakeFiles/Scheduling_Algorithm.dir/build.make
Scheduling_Algorithm: CMakeFiles/Scheduling_Algorithm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/karaya_12/Coding/Operating System Concepts/Assignment III/Scheduling_Algorithm/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Scheduling_Algorithm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Scheduling_Algorithm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Scheduling_Algorithm.dir/build: Scheduling_Algorithm

.PHONY : CMakeFiles/Scheduling_Algorithm.dir/build

CMakeFiles/Scheduling_Algorithm.dir/requires: CMakeFiles/Scheduling_Algorithm.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Scheduling_Algorithm.dir/requires

CMakeFiles/Scheduling_Algorithm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Scheduling_Algorithm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Scheduling_Algorithm.dir/clean

CMakeFiles/Scheduling_Algorithm.dir/depend:
	cd "/home/karaya_12/Coding/Operating System Concepts/Assignment III/Scheduling_Algorithm/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/karaya_12/Coding/Operating System Concepts/Assignment III/Scheduling_Algorithm" "/home/karaya_12/Coding/Operating System Concepts/Assignment III/Scheduling_Algorithm" "/home/karaya_12/Coding/Operating System Concepts/Assignment III/Scheduling_Algorithm/cmake-build-debug" "/home/karaya_12/Coding/Operating System Concepts/Assignment III/Scheduling_Algorithm/cmake-build-debug" "/home/karaya_12/Coding/Operating System Concepts/Assignment III/Scheduling_Algorithm/cmake-build-debug/CMakeFiles/Scheduling_Algorithm.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Scheduling_Algorithm.dir/depend

