# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/blackdracula/dev/display-manager

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/blackdracula/dev/display-manager/build

# Include any dependencies generated for this target.
include CMakeFiles/display-manager.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/display-manager.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/display-manager.dir/flags.make

CMakeFiles/display-manager.dir/display-manager_autogen/mocs_compilation.cpp.o: CMakeFiles/display-manager.dir/flags.make
CMakeFiles/display-manager.dir/display-manager_autogen/mocs_compilation.cpp.o: display-manager_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blackdracula/dev/display-manager/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/display-manager.dir/display-manager_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/display-manager.dir/display-manager_autogen/mocs_compilation.cpp.o -c /home/blackdracula/dev/display-manager/build/display-manager_autogen/mocs_compilation.cpp

CMakeFiles/display-manager.dir/display-manager_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/display-manager.dir/display-manager_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blackdracula/dev/display-manager/build/display-manager_autogen/mocs_compilation.cpp > CMakeFiles/display-manager.dir/display-manager_autogen/mocs_compilation.cpp.i

CMakeFiles/display-manager.dir/display-manager_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/display-manager.dir/display-manager_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blackdracula/dev/display-manager/build/display-manager_autogen/mocs_compilation.cpp -o CMakeFiles/display-manager.dir/display-manager_autogen/mocs_compilation.cpp.s

CMakeFiles/display-manager.dir/main.cpp.o: CMakeFiles/display-manager.dir/flags.make
CMakeFiles/display-manager.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blackdracula/dev/display-manager/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/display-manager.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/display-manager.dir/main.cpp.o -c /home/blackdracula/dev/display-manager/main.cpp

CMakeFiles/display-manager.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/display-manager.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blackdracula/dev/display-manager/main.cpp > CMakeFiles/display-manager.dir/main.cpp.i

CMakeFiles/display-manager.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/display-manager.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blackdracula/dev/display-manager/main.cpp -o CMakeFiles/display-manager.dir/main.cpp.s

CMakeFiles/display-manager.dir/loginwindow.cpp.o: CMakeFiles/display-manager.dir/flags.make
CMakeFiles/display-manager.dir/loginwindow.cpp.o: ../loginwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blackdracula/dev/display-manager/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/display-manager.dir/loginwindow.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/display-manager.dir/loginwindow.cpp.o -c /home/blackdracula/dev/display-manager/loginwindow.cpp

CMakeFiles/display-manager.dir/loginwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/display-manager.dir/loginwindow.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blackdracula/dev/display-manager/loginwindow.cpp > CMakeFiles/display-manager.dir/loginwindow.cpp.i

CMakeFiles/display-manager.dir/loginwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/display-manager.dir/loginwindow.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blackdracula/dev/display-manager/loginwindow.cpp -o CMakeFiles/display-manager.dir/loginwindow.cpp.s

# Object files for target display-manager
display__manager_OBJECTS = \
"CMakeFiles/display-manager.dir/display-manager_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/display-manager.dir/main.cpp.o" \
"CMakeFiles/display-manager.dir/loginwindow.cpp.o"

# External object files for target display-manager
display__manager_EXTERNAL_OBJECTS =

display-manager: CMakeFiles/display-manager.dir/display-manager_autogen/mocs_compilation.cpp.o
display-manager: CMakeFiles/display-manager.dir/main.cpp.o
display-manager: CMakeFiles/display-manager.dir/loginwindow.cpp.o
display-manager: CMakeFiles/display-manager.dir/build.make
display-manager: /usr/lib/libQt5Widgets.so.5.14.1
display-manager: /usr/lib/libQt5Gui.so.5.14.1
display-manager: /usr/lib/libQt5Core.so.5.14.1
display-manager: CMakeFiles/display-manager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/blackdracula/dev/display-manager/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable display-manager"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/display-manager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/display-manager.dir/build: display-manager

.PHONY : CMakeFiles/display-manager.dir/build

CMakeFiles/display-manager.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/display-manager.dir/cmake_clean.cmake
.PHONY : CMakeFiles/display-manager.dir/clean

CMakeFiles/display-manager.dir/depend:
	cd /home/blackdracula/dev/display-manager/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/blackdracula/dev/display-manager /home/blackdracula/dev/display-manager /home/blackdracula/dev/display-manager/build /home/blackdracula/dev/display-manager/build /home/blackdracula/dev/display-manager/build/CMakeFiles/display-manager.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/display-manager.dir/depend

