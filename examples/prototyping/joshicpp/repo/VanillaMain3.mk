CXX=g++
CXXFLAGS=-std=c++11 -Wall -g -I./include/
BIN_DIR=bin
SRC_DIR=source
MAIN_DIR=mains
TARGET=$(BIN_DIR)/vanillamain3
MAIN_FILES=$(MAIN_DIR)/VanillaMain3.cpp
FILES=$(SRC_DIR)/Random1.cpp $(SRC_DIR)/PayOff3.cpp $(SRC_DIR)/PayOffBridge.cpp $(SRC_DIR)/SimpleMC5.cpp $(SRC_DIR)/Vanilla3.cpp

all:$(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(MAIN_FILES) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)

# Debugging info
print-%  : ; @echo $* = $($*)
