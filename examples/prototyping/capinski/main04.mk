CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main04
FILES=Main04.cpp BinModel01.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


