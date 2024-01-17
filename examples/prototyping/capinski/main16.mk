CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main16
FILES=Main16.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


