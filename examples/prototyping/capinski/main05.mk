CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main05
FILES=Main05.cpp BinModel01.cpp Options01.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


