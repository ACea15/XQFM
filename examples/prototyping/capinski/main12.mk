CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main12
FILES=Main12.cpp BinModel02.cpp Options07.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


