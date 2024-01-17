CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main06
FILES=Main06.cpp BinModel01.cpp Options02.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


