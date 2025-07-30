CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -pthread

INCLUDES = -Iinclude
SRC = $(wildcard src/*.cpp)
TEST = test/main.cpp
TARGET = test_allocator

all: $(TARGET)

$(TARGET): $(SRC) $(TEST)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

clean:
	rm -f $(TARGET)
