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
CMAKE_COMMAND = /snap/clion/57/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/57/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/victoroff/CLionProjects/Soft_Processor/CPU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/victoroff/CLionProjects/Soft_Processor/CPU/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CPU.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CPU.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CPU.dir/flags.make

CMakeFiles/CPU.dir/main.cpp.o: CMakeFiles/CPU.dir/flags.make
CMakeFiles/CPU.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/victoroff/CLionProjects/Soft_Processor/CPU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CPU.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CPU.dir/main.cpp.o -c /home/victoroff/CLionProjects/Soft_Processor/CPU/main.cpp

CMakeFiles/CPU.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CPU.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/victoroff/CLionProjects/Soft_Processor/CPU/main.cpp > CMakeFiles/CPU.dir/main.cpp.i

CMakeFiles/CPU.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CPU.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/victoroff/CLionProjects/Soft_Processor/CPU/main.cpp -o CMakeFiles/CPU.dir/main.cpp.s

CMakeFiles/CPU.dir/cpu.cpp.o: CMakeFiles/CPU.dir/flags.make
CMakeFiles/CPU.dir/cpu.cpp.o: ../cpu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/victoroff/CLionProjects/Soft_Processor/CPU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CPU.dir/cpu.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CPU.dir/cpu.cpp.o -c /home/victoroff/CLionProjects/Soft_Processor/CPU/cpu.cpp

CMakeFiles/CPU.dir/cpu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CPU.dir/cpu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/victoroff/CLionProjects/Soft_Processor/CPU/cpu.cpp > CMakeFiles/CPU.dir/cpu.cpp.i

CMakeFiles/CPU.dir/cpu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CPU.dir/cpu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/victoroff/CLionProjects/Soft_Processor/CPU/cpu.cpp -o CMakeFiles/CPU.dir/cpu.cpp.s

CMakeFiles/CPU.dir/stack_dir/stack.cpp.o: CMakeFiles/CPU.dir/flags.make
CMakeFiles/CPU.dir/stack_dir/stack.cpp.o: ../stack_dir/stack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/victoroff/CLionProjects/Soft_Processor/CPU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CPU.dir/stack_dir/stack.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CPU.dir/stack_dir/stack.cpp.o -c /home/victoroff/CLionProjects/Soft_Processor/CPU/stack_dir/stack.cpp

CMakeFiles/CPU.dir/stack_dir/stack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CPU.dir/stack_dir/stack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/victoroff/CLionProjects/Soft_Processor/CPU/stack_dir/stack.cpp > CMakeFiles/CPU.dir/stack_dir/stack.cpp.i

CMakeFiles/CPU.dir/stack_dir/stack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CPU.dir/stack_dir/stack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/victoroff/CLionProjects/Soft_Processor/CPU/stack_dir/stack.cpp -o CMakeFiles/CPU.dir/stack_dir/stack.cpp.s

# Object files for target CPU
CPU_OBJECTS = \
"CMakeFiles/CPU.dir/main.cpp.o" \
"CMakeFiles/CPU.dir/cpu.cpp.o" \
"CMakeFiles/CPU.dir/stack_dir/stack.cpp.o"

# External object files for target CPU
CPU_EXTERNAL_OBJECTS =

CPU: CMakeFiles/CPU.dir/main.cpp.o
CPU: CMakeFiles/CPU.dir/cpu.cpp.o
CPU: CMakeFiles/CPU.dir/stack_dir/stack.cpp.o
CPU: CMakeFiles/CPU.dir/build.make
CPU: CMakeFiles/CPU.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/victoroff/CLionProjects/Soft_Processor/CPU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable CPU"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CPU.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CPU.dir/build: CPU

.PHONY : CMakeFiles/CPU.dir/build

CMakeFiles/CPU.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CPU.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CPU.dir/clean

CMakeFiles/CPU.dir/depend:
	cd /home/victoroff/CLionProjects/Soft_Processor/CPU/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/victoroff/CLionProjects/Soft_Processor/CPU /home/victoroff/CLionProjects/Soft_Processor/CPU /home/victoroff/CLionProjects/Soft_Processor/CPU/cmake-build-debug /home/victoroff/CLionProjects/Soft_Processor/CPU/cmake-build-debug /home/victoroff/CLionProjects/Soft_Processor/CPU/cmake-build-debug/CMakeFiles/CPU.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CPU.dir/depend
