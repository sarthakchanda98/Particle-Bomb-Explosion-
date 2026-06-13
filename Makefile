# Makefile for Particle Explosion Project (SDL3)

CXX = g++
CXXFLAGS = -g -Wall -I/usr/local/include/SDL3
LDFLAGS = -L/usr/local/lib -lSDL3

SRCS = main.cpp particle.cpp swarm.cpp screen.cpp gradient.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run
