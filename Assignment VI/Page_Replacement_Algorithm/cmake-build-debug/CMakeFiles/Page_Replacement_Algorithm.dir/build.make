# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /home/karaya_12/Program/clion-2018.3.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/karaya_12/Program/clion-2018.3.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/karaya_12/Coding/Operating System Concepts/Assignment VI/Page_Replacement_Algorithm"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/karaya_12/Coding/Operating System Concepts/Assignment VI/Page_Replacement_Algorithm/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Page_Replacement_Algorithm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Page_Replacement_Algorithm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Page_Replacement_Algorithm.dir/flags.make

CMakeFiles/Page_Replacement_Algorithm.dir/main.cpp.o: CMakeFiles/Page_Replacement_Algorithm.dir/flags.make
CMakeFiles/Page_Replacement_Algorithm.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/karaya_12/Coding/Operating System Concepts/Assignment VI/Page_Replacement_Algorithm/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Page_Replacement_Algorithm.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Page_Replacement_Algorithm.dir/main.cpp.o -c "/home/karaya_12/Coding/Operating System Concepts/Assignment VI/Page_Replacement_Algorithm/main.cpp"

CMakeFiles/Page_Replacement_Algorithm.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Page_Replacement_Algorithm.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/karaya_12/Coding/Operating System Concepts/Assignment VI/Page_Replacement_Algorithm/main.cpp" > CMakeFiles/Page_Replacement_Algorithm.dir/main.cpp.i

CMakeFiles/Page_Replacement_Algorithm.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Page_Replacement_Algorithm.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/karaya_12/Coding/Operating System Concepts/Assignment VI/Page_Replacement_Algorithm/main.cpp" -o CMakeFiles/Page_Replacement_Algorithm.dir/main.cpp.s

# Object files for target Page_Replacement_Algorithm
Page_Replacement_Algorithm_OBJECTS = \
"CMakeFiles/Page_Replacement_Algorithm.dir/main.cpp.o"

# External object files for target Page_Replacement_Algorithm
Page_Replacement_Algorithm_EXTERNAL_OBJECTS =

Page_Replacement_Algorithm: CMakeFiles/Page_Replacement_Algorithm.dir/main.cpp.o
Page_Replacement_Algorithm: CMakeFiles/Page_Replacement_Algorithm.dir/build.make
Page_Replacement_Algorithm: CMakeFiles/Page_Replacement_Algorithm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/karaya_12/Coding/Operating System Concepts/Assignment VI/Page_Replacement_Algorithm/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Page_Replacement_Algorithm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Page_Replacement_Algorithm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Page_Replacement_Algorithm.dir/build: Page_Replacement_Algorithm

.PHONY : CMakeFiles/Page_Replacement_Algorithm.dir/build

CMakeFiles/Page_Replacement_Algorithm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Page_Replacement_Algorithm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Page_Replacement_Algorithm.dir/clean

CMakeFiles/Page_Replacement_Algorithm.dir/depend:
	cd "/home/karaya_12/Coding/Operating System Concepts/Assignment VI/Page_Replacement_Algorithm/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/karaya_12/Coding/Operating System Concepts/Assignment VI/Page_Replacement_Algorithm" "/home/karaya_12/Coding/Operating System Concepts/Assignment VI/Page_Replacement_Algorithm" "/home/karaya_12/Coding/Operating System Concepts/Assignment VI/Page_Replacement_Algorithm/cmake-build-debug" "/home/karaya_12/Coding/Operating System Concepts/Assignment VI/Page_Replacement_Algorithm/cmake-build-debug" "/home/karaya_12/Coding/Operating System Concepts/Assignment VI/Page_Replacement_Algorithm/cmake-build-debug/CMakeFiles/Page_Replacement_Algorithm.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Page_Replacement_Algorithm.dir/depend

