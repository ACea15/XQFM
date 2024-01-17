CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main19
FILES=Main19.cpp PathDepOption01.cpp BSModel01.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


