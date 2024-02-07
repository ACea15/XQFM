CXX=g++
CXXFLAGS=-std=c++11 -Wall -g -I./include/
BIN_DIR=bin
SRC_DIR=source
MAIN_DIR=mains
TARGET=$(BIN_DIR)/simplemcmain1
MAIN_FILES=$(MAIN_DIR)/SimpleMCMain1.cpp
FILES=$(SRC_DIR)/Random1.cpp

all:$(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(MAIN_FILES) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)

# Debugging info
print-%  : ; @echo $* = $($*)
