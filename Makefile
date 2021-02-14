# My third makefile

# Name of the project
PROJ_NAME=a

# .cpp files
CPP_SOURCE=$(wildcard ./src/*.cpp)

# .h files
H_SOURCE=$(wildcard ./include/*.h)

# Object files
OBJ=$(subst .cpp,.o,$(subst src,build,$(CPP_SOURCE)))

# Compiler and linker
CC=g++

# Flags for compiler
CC_FLAGS= -c -g -W -Wall -ansi -pedantic -std=c++11 -I ./include

# Command used at clean target
RM = rm -rf

#
# Compilation and linking
#
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '

./build/%.o: ./src/%.cpp ./include/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./build/main.o: ./src/main.cpp $(H_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p build

clean:
	@ $(RM) ./build/*.o $(PROJ_NAME) *~
	@ rmdir build

.PHONY: all clean
