CXX=g++
CXXFLAGS=-O3 -march=native -pthread -ftree-vectorize -flto
TARGET=mc1_concurrency
# FILES=../Futils/Config.cpp XMatrix.cpp mc1_concurrency.cpp
FILES=XMatrix.cpp mc1_concurrency.cpp
all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
