CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=main22
FILES=Main22.cpp PathDepOption04.cpp  GmtrAsianCall.cpp EurCall.cpp BSModel01.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


