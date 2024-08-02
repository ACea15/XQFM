CXX=g++
# CXXFLAGS=-O3 -march=native -pthread #-ftree-vectorize
TARGET=mc1
FILES=../Futils/Config.cpp XMatrix.cpp mc1.cpp

all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
