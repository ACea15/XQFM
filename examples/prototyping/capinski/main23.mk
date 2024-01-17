CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main23
FILES=Main23.cpp PathDepOption05.cpp BSModel02.cpp Matrix.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


