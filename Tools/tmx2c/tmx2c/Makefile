CC=gcc
CXX=clang++
#CFLAGS= -O0 -g -std=c++11 -mmacosx-version-min=10.11 -Wextra -Wall -F/Library/Frameworks -I../include -I-../include
CFLAGS=-O0 -g -std=c++11 -mmacosx-version-min=10.9 -F/Library/Frameworks -I../include -I-../include
LIBS=-lc++ -lc
#LIBS=-framework SDL2 -framework SDL2_image -lc++ -lc
LDFLAGS=-macosx_version_min 10.9
# -framework SDL2 -framework SDL2_image

CFILES=main.cpp tinyxml2.cpp

OBJS=$(CFILES:.cpp=.o)

all: build

install: build
	sudo cp tmx2c /usr/bin

build: main.o tinyxml2.o
	$(LD) $(LDFLAGS) -o tmx2c $(LIBS) $^

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@  $<

clean:
	rm -f tmx2c $(OBJS) *.o
