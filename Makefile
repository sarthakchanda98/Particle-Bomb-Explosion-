# Compiler definitions
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 $(shell pkg-config --cflags sdl3)
LIBS = $(shell pkg-config --libs sdl3)

# Target executable name
TARGET = molecular_simulator

# List of all source files in your project
SRCS = main.cpp screen.cpp particle.cpp swarm.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target rule
all: $(TARGET)

# Link object files together into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Compile each .cpp file into a .o object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
