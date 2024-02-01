CXX=g++
CXXFLAGS=-std=c++11 -Wall -g -I$(HOME)/projects/CoDiPack/include/
TARGET=main08ad
FILES=Main08AD.cpp 

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


