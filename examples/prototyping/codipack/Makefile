CXX=g++
CXXFLAGS=-std=c++11 -Wall -g -I$(HOME)/projects/CoDiPack/include/
LDFLAGS=-I$(HOME)/projects/CoDiPack/include/

SRC_DIR := $(PWD)
OBJ_DIR := $(PWD)
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TGT_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%,$(SRC_FILES))
# LDFLAGS := ...
# CPPFLAGS := ...
# CXXFLAGS := ...

# # .PHONY means these rules get executed even if
# # files of those names exist.
# .PHONY: all clean

all: $(TGT_FILES)
# rm -f $(OBJ_FILES)
$(TGT_FILES): % : %.o 
	$(CXX) $(LDFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TGT_FILES)
