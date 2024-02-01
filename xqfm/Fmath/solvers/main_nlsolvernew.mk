CXX=g++
CXXFLAGS=-std=c++11 -Wall -g -I$(HOME)/projects/CoDiPack/include/
TARGET=main_nlsolver
FILES=$(wildcard $(*.cpp))
OBJ_FILES := $(patsubst %.cpp,%.o,$(FILES))
TGT_FILES := $(patsubst %.cpp,%,$(FILES))

all: $(TGT_FILES)
# rm -f $(OBJ_FILES)
$(TGT_FILES): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -MMD -o $@ -c $<

clean:
	rm -f $(TGT_FILES)


# all:$(TARGET)

# $(TARGET): $(FILES)
# 	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)
# $(FILES) : nlsolver.hpp
# clean:
# 	rm -f $(TARGET)

-include $(OBJS:.o=.d)
