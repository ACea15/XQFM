CXX=g++
CXXFLAGS=-std=c++11 -Wall -I$(HOME)/projects/CoDiPack/include/
TARGET=main1
FILES=main1.cpp BinOptions.cpp BinModel.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)


