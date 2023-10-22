CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=simplemc2
FILES=SimpleMCMain2.cpp PayOff1.cpp SimpleMC.cpp Random1.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


