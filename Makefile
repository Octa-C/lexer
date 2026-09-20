CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

ifeq ($(OS),Windows_NT)
  EXE = .exe
endif

TARGET = build/lexer$(EXE)
SRCS   = main.cpp $(wildcard src/*.cpp)
OBJS   = $(patsubst %.cpp,build/%.o,$(notdir $(SRCS)))
HDRS   = $(wildcard include/*.hpp)

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

build/main.o: main.cpp $(HDRS) | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%.o: src/%.cpp $(HDRS) | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

# make test ARGS=-v lists every error in each failing case
test: $(TARGET)
	python3 -m pytest tests $(ARGS)

clean:
	rm -rf build
