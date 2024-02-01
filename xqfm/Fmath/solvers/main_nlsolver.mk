#https://copyprogramming.com/howto/how-to-make-makefile-recompile-when-a-header-file-is-changed
CXX=g++
CXXFLAGS=-std=c++11 -Wall -g -I$(HOME)/projects/CoDiPack/include/
TARGET=main_nlsolver
FILES=main_nlsolver.cpp 

all:$(TARGET)

$(TARGET): $(FILES) nlsolver.hpp
	$(CXX) $(CXXFLAGS) $(filter-out %.hpp,$^) -o $@
$(FILES) : nlsolver.hpp
clean:
	rm -f $(TARGET)
