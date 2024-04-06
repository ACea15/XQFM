CXX=g++
CXXFLAGS=-std=c++11 -Wall -g -I./include/
BIN_DIR=bin
SRC_DIR=source
MAIN_DIR=mains
TARGET=$(BIN_DIR)/treemain
MAIN_FILES=$(MAIN_DIR)/TreeMain.cpp
FILES=$(SRC_DIR)/Arrays.cpp $(SRC_DIR)/BinomialTree.cpp $(SRC_DIR)/BlackScholesFormulas.cpp \
$(SRC_DIR)/Normals.cpp  $(SRC_DIR)/Parameters.cpp $(SRC_DIR)/PayOff3.cpp $(SRC_DIR)/PayOffBridge.cpp \
$(SRC_DIR)/PayOffForward.cpp $(SRC_DIR)/TreeAmerican.cpp $(SRC_DIR)/TreeEuropean.cpp $(SRC_DIR)/TreeProducts.cpp

all:$(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(MAIN_FILES) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)

# Debugging info
print-%  : ; @echo $* = $($*)
