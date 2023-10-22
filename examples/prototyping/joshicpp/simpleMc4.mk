CXX=g++
CXXFLAGS=-std=c++11 -Wall -g
TARGET=simplemc4
FILES=SimpleMCMain4.cpp PayOff2.cpp SimpleMC2.cpp Random1.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


