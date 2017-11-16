FSOURCES = framework/main.cpp framework/gfx.cpp framework/debugger.cpp 
CSOURCES = sys_debug_scmp.cpp sys_processor.cpp hardware.cpp

CC = g++

all: scmpmc

clean:
	rm -f wmscmpmc *.o

.PHONY: all clean

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

CFLAGS := $(SDL_CFLAGS) -O2 -Wall -DMODEL2KRAM -DINCLUDE_DEBUGGING_SUPPORT -I. -I./framework -I./common -Wno-unused-variable
LDFLAGS := $(SDL_LDFLAGS) -lSDL2_image

scmpmc : $(FSOURCES) $(CSOURCES)
	$(CC) $(FSOURCES) $(CSOURCES) $(CFLAGS) $(LDFLAGS) -o $@



