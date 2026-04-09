TARGET = pe-parser
BUILD_DIR = build

SRCS = $(shell find . -name "*.cpp")
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -I.

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
