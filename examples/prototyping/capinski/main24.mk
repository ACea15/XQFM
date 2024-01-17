CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main24
FILES=Main24.cpp BSEq.cpp Option.cpp BSModel01.cpp ExplicitMethod.cpp FDMethod.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


