# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/shyu/Desktop/final_project_all

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shyu/Desktop/final_project_all

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/shyu/Desktop/final_project_all/CMakeFiles /home/shyu/Desktop/final_project_all/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/shyu/Desktop/final_project_all/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named main

# Build rule for target.
main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 main
.PHONY : main

# fast build rule for target.
main/fast:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/build
.PHONY : main/fast

#=============================================================================
# Target rules for targets named show_board

# Build rule for target.
show_board: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 show_board
.PHONY : show_board

# fast build rule for target.
show_board/fast:
	$(MAKE) -f CMakeFiles/show_board.dir/build.make CMakeFiles/show_board.dir/build
.PHONY : show_board/fast

#=============================================================================
# Target rules for targets named Puyo_test

# Build rule for target.
Puyo_test: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Puyo_test
.PHONY : Puyo_test

# fast build rule for target.
Puyo_test/fast:
	$(MAKE) -f CMakeFiles/Puyo_test.dir/build.make CMakeFiles/Puyo_test.dir/build
.PHONY : Puyo_test/fast

Collision.o: Collision.cpp.o

.PHONY : Collision.o

# target to build an object file
Collision.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Collision.cpp.o
.PHONY : Collision.cpp.o

Collision.i: Collision.cpp.i

.PHONY : Collision.i

# target to preprocess a source file
Collision.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Collision.cpp.i
.PHONY : Collision.cpp.i

Collision.s: Collision.cpp.s

.PHONY : Collision.s

# target to generate assembly for a file
Collision.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Collision.cpp.s
.PHONY : Collision.cpp.s

ECS/ECS.o: ECS/ECS.cpp.o

.PHONY : ECS/ECS.o

# target to build an object file
ECS/ECS.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/ECS/ECS.cpp.o
.PHONY : ECS/ECS.cpp.o

ECS/ECS.i: ECS/ECS.cpp.i

.PHONY : ECS/ECS.i

# target to preprocess a source file
ECS/ECS.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/ECS/ECS.cpp.i
.PHONY : ECS/ECS.cpp.i

ECS/ECS.s: ECS/ECS.cpp.s

.PHONY : ECS/ECS.s

# target to generate assembly for a file
ECS/ECS.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/ECS/ECS.cpp.s
.PHONY : ECS/ECS.cpp.s

Game.o: Game.cpp.o

.PHONY : Game.o

# target to build an object file
Game.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Game.cpp.o
.PHONY : Game.cpp.o

Game.i: Game.cpp.i

.PHONY : Game.i

# target to preprocess a source file
Game.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Game.cpp.i
.PHONY : Game.cpp.i

Game.s: Game.cpp.s

.PHONY : Game.s

# target to generate assembly for a file
Game.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Game.cpp.s
.PHONY : Game.cpp.s

GameBoard.o: GameBoard.cpp.o

.PHONY : GameBoard.o

# target to build an object file
GameBoard.cpp.o:
	$(MAKE) -f CMakeFiles/Puyo_test.dir/build.make CMakeFiles/Puyo_test.dir/GameBoard.cpp.o
.PHONY : GameBoard.cpp.o

GameBoard.i: GameBoard.cpp.i

.PHONY : GameBoard.i

# target to preprocess a source file
GameBoard.cpp.i:
	$(MAKE) -f CMakeFiles/Puyo_test.dir/build.make CMakeFiles/Puyo_test.dir/GameBoard.cpp.i
.PHONY : GameBoard.cpp.i

GameBoard.s: GameBoard.cpp.s

.PHONY : GameBoard.s

# target to generate assembly for a file
GameBoard.cpp.s:
	$(MAKE) -f CMakeFiles/Puyo_test.dir/build.make CMakeFiles/Puyo_test.dir/GameBoard.cpp.s
.PHONY : GameBoard.cpp.s

GameObject.o: GameObject.cpp.o

.PHONY : GameObject.o

# target to build an object file
GameObject.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/GameObject.cpp.o
.PHONY : GameObject.cpp.o

GameObject.i: GameObject.cpp.i

.PHONY : GameObject.i

# target to preprocess a source file
GameObject.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/GameObject.cpp.i
.PHONY : GameObject.cpp.i

GameObject.s: GameObject.cpp.s

.PHONY : GameObject.s

# target to generate assembly for a file
GameObject.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/GameObject.cpp.s
.PHONY : GameObject.cpp.s

Map.o: Map.cpp.o

.PHONY : Map.o

# target to build an object file
Map.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Map.cpp.o
.PHONY : Map.cpp.o

Map.i: Map.cpp.i

.PHONY : Map.i

# target to preprocess a source file
Map.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Map.cpp.i
.PHONY : Map.cpp.i

Map.s: Map.cpp.s

.PHONY : Map.s

# target to generate assembly for a file
Map.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Map.cpp.s
.PHONY : Map.cpp.s

Puyo_test.o: Puyo_test.cpp.o

.PHONY : Puyo_test.o

# target to build an object file
Puyo_test.cpp.o:
	$(MAKE) -f CMakeFiles/Puyo_test.dir/build.make CMakeFiles/Puyo_test.dir/Puyo_test.cpp.o
.PHONY : Puyo_test.cpp.o

Puyo_test.i: Puyo_test.cpp.i

.PHONY : Puyo_test.i

# target to preprocess a source file
Puyo_test.cpp.i:
	$(MAKE) -f CMakeFiles/Puyo_test.dir/build.make CMakeFiles/Puyo_test.dir/Puyo_test.cpp.i
.PHONY : Puyo_test.cpp.i

Puyo_test.s: Puyo_test.cpp.s

.PHONY : Puyo_test.s

# target to generate assembly for a file
Puyo_test.cpp.s:
	$(MAKE) -f CMakeFiles/Puyo_test.dir/build.make CMakeFiles/Puyo_test.dir/Puyo_test.cpp.s
.PHONY : Puyo_test.cpp.s

TextureManager.o: TextureManager.cpp.o

.PHONY : TextureManager.o

# target to build an object file
TextureManager.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/TextureManager.cpp.o
.PHONY : TextureManager.cpp.o

TextureManager.i: TextureManager.cpp.i

.PHONY : TextureManager.i

# target to preprocess a source file
TextureManager.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/TextureManager.cpp.i
.PHONY : TextureManager.cpp.i

TextureManager.s: TextureManager.cpp.s

.PHONY : TextureManager.s

# target to generate assembly for a file
TextureManager.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/TextureManager.cpp.s
.PHONY : TextureManager.cpp.s

Vector2D.o: Vector2D.cpp.o

.PHONY : Vector2D.o

# target to build an object file
Vector2D.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Vector2D.cpp.o
.PHONY : Vector2D.cpp.o

Vector2D.i: Vector2D.cpp.i

.PHONY : Vector2D.i

# target to preprocess a source file
Vector2D.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Vector2D.cpp.i
.PHONY : Vector2D.cpp.i

Vector2D.s: Vector2D.cpp.s

.PHONY : Vector2D.s

# target to generate assembly for a file
Vector2D.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Vector2D.cpp.s
.PHONY : Vector2D.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.s
.PHONY : main.cpp.s

test_fall_board.o: test_fall_board.cpp.o

.PHONY : test_fall_board.o

# target to build an object file
test_fall_board.cpp.o:
	$(MAKE) -f CMakeFiles/show_board.dir/build.make CMakeFiles/show_board.dir/test_fall_board.cpp.o
.PHONY : test_fall_board.cpp.o

test_fall_board.i: test_fall_board.cpp.i

.PHONY : test_fall_board.i

# target to preprocess a source file
test_fall_board.cpp.i:
	$(MAKE) -f CMakeFiles/show_board.dir/build.make CMakeFiles/show_board.dir/test_fall_board.cpp.i
.PHONY : test_fall_board.cpp.i

test_fall_board.s: test_fall_board.cpp.s

.PHONY : test_fall_board.s

# target to generate assembly for a file
test_fall_board.cpp.s:
	$(MAKE) -f CMakeFiles/show_board.dir/build.make CMakeFiles/show_board.dir/test_fall_board.cpp.s
.PHONY : test_fall_board.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... main"
	@echo "... rebuild_cache"
	@echo "... show_board"
	@echo "... Puyo_test"
	@echo "... Collision.o"
	@echo "... Collision.i"
	@echo "... Collision.s"
	@echo "... ECS/ECS.o"
	@echo "... ECS/ECS.i"
	@echo "... ECS/ECS.s"
	@echo "... Game.o"
	@echo "... Game.i"
	@echo "... Game.s"
	@echo "... GameBoard.o"
	@echo "... GameBoard.i"
	@echo "... GameBoard.s"
	@echo "... GameObject.o"
	@echo "... GameObject.i"
	@echo "... GameObject.s"
	@echo "... Map.o"
	@echo "... Map.i"
	@echo "... Map.s"
	@echo "... Puyo_test.o"
	@echo "... Puyo_test.i"
	@echo "... Puyo_test.s"
	@echo "... TextureManager.o"
	@echo "... TextureManager.i"
	@echo "... TextureManager.s"
	@echo "... Vector2D.o"
	@echo "... Vector2D.i"
	@echo "... Vector2D.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... test_fall_board.o"
	@echo "... test_fall_board.i"
	@echo "... test_fall_board.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

