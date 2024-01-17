CXX=g++
CXXFLAGS=-std=c++11 -Wall -I$(HOME)/projects/CoDiPack/include/
TARGET=main_nlsolver
FILES=main_nlsolver.cpp 

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
