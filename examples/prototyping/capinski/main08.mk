CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main08
FILES=Main08.cpp BinModel02.cpp Options04.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


