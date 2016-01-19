CC=gcc
CXX=clang++
#CFLAGS= -O0 -g -std=c++11 -mmacosx-version-min=10.11 -Wextra -Wall -F/Library/Frameworks -I../include -I-../include
CFLAGS=-O0 -g -std=c++11 -mmacosx-version-min=10.9 -F/Library/Frameworks -I../include -I-../include
LIBS=-framework SDL2 -framework SDL2_image -lc++ -lc
LDFLAGS=-macosx_version_min 10.9 -framework SDL2 -framework SDL2_image


CFILES=tmx2c.cpp

OBJS=$(CFILES:.cpp=.o)

all: build

install: build
	sudo cp png2tilefest /usr/local/bin
	
build: $(OBJS)
	$(LD) $(LDFLAGS) -o png2tilefest $(LIBS) $^

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@  $<

clean:
	rm -f png2tilefest $(OBJS) *.o
