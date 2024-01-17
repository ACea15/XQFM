CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main15
FILES=Main15.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


