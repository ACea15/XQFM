CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main02
FILES=Main02.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


