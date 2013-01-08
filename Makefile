#CXX = i586-mingw32msvc-g++
CXXSRC=$(shell find src -name "*.cpp")
SOURCES= $(CXXSRC) include/SDL/SDL_video.h include/SDL/SDL_mixer.h
CXXOBJS=$(SOURCES:.cpp=.o)
#CFLAGS= -g   # for debug
CFLAGS=
#CXXFLAGS=-g -Iinclude/SDL -Iinclude/GL -Ibulletml -Isrc -I/usr/X11R6/include/    # for debug
CXXFLAGS=-O2 -Iinclude/SDL -Iinclude/GL -Ibulletml -Isrc -I/usr/X11R6/include/ 
#CXXFLAGS=-g -Iinclude/SDL -Iinclude/GL -Ibulletml -Isrc -I/usr/X11R6/include/ -I/usr/local/include   # for MinGW debug
#CXXFLAGS=-O2 -Iinclude/SDL -Iinclude/GL -Ibulletml -Isrc -I/usr/X11R6/include/ -I/usr/local/include   # for MinGW
EXE=p47_cpp
#EXE=p47_cpp.exe
COBJS=src/dirent_d.o 

all: $(EXE)

$(EXE): bulletml/libbulletml_d.a $(CXXOBJS) $(COBJS)
	gcc $(CFLAGS) -o $@ $(CXXOBJS) $(COBJS) bulletml/libbulletml_d.a -L/usr/local/lib -L/usr/lib -lGLU -lGL -lglut -lm -lstdc++ -lSDL -lSDL_mixer 
#	i586-mingw32msvc-gcc $(CFLAGS) -o $@ $(CXXOBJS) $(COBJS) bulletml/libbulletml_d.a libSDL.a libSDL_mixer.a libglut.a -L/usr/local/lib -I/usr/local/include -Iinclude/SDL -lopengl32 -lglu32 -lm -lstdc++ 

src/dirent_d.o: src/dirent_d.c
	gcc -c $< -o $@
#	i586-mingw32msvc-gcc -c $< -o $@

bulletml/libbulletml_d.a:
	make -C bulletml

clean_bulletml:
	make -C bulletml clean

clean: clean_bulletml
	rm src/*.o
	rm src/abagames/p47/*.o
	rm src/abagames/util/*.o
	rm src/abagames/util/sdl/*.o
	rm src/abagames/util/bulletml/*.o
