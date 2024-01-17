CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main07
FILES=Main07.cpp BinModel01.cpp Options03.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


