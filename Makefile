# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Iinclude 
LDFLAGS := -lraylib -lcjson
# Directories
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build

# Source files and objects
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Target executable
TARGET := $(BUILD_DIR)/main

# Default target
all: $(TARGET)

# Link object files into the executable
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ ${LDFLAGS}

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean