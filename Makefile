CC = g++
F = -c
CFLAGS= -pthread -lSDL2 -lSDL2_image -lSDL2_ttf -cpp=17

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: windy

windy: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(CFLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(F) $(CFLAGS)
clean:
	rm -f $(OBJECTS)
