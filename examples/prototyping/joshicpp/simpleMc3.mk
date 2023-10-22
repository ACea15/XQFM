CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=simplemc3
FILES=SimpleMCMain3.cpp PayOff2.cpp SimpleMC2.cpp Random1.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


