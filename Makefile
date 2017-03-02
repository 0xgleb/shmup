# A simple Makefile for compiling small SDL projects

# set the compiler
CC := g++

# set the compiler flags
FLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2main -lSDL2 -lSDL2_image -lm -ggdb

# add header files here
HDRS := include/list.hpp include/vector.hpp include/body.hpp include/sdl.hpp include/constant.hpp 

# add source files here
SRCS := src/list.cpp src/vector.cpp src/body.cpp src/sdl.cpp src/constant.cpp main.cpp 

# generate names of object files
OBJS := $(SRCS:.cpp=.o)

# name of executable
EXEC := out

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(FLAGS)

# recipe for building object files
$(OBJS): $(@:.o=.cpp) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.cpp) -c $(FLAGS)

# recipe to clean the workspace
clean:
	rm -vf $(EXEC) $(OBJS)

.PHONY: all clean
