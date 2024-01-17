CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main14
FILES=Main14.cpp BinModel02.cpp Options09.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


