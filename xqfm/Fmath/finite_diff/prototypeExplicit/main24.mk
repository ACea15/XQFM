CXX=g++
CXXFLAGS:=-std=c++11 -Wall -g -I$(HOME)/projects/CoDiPack/include/
TARGET=main24
FILES=Main24.cpp BSEq.cpp Option.cpp BSModel01.cpp ExplicitMethod.cpp FDMethod.cpp

# VAR="HELLO"
# $(info VAR is $(VAR))
# $(warning VAR is $(VAR))
# $(error VAR is $(VAR))

# USE_CODIFORWARD=false
# USE_CODIREVERSE=false
ifeq ($(USE_CODIFORWARD),true)
    CODITYPE:=-DUSE_CODIFORWARD
    DOUBLETYPE:="CODI FORWARD"
else
    ifeq ($(USE_CODIREVERSE),true)
    CODITYPE:=-DUSE_CODIREVERSE
    DOUBLETYPE:="CODI REVERSE"
    else
    CODITYPE:=
    DOUBLETYPE:="DOUBLE"
    endif
endif


$(info Double type will be $(DOUBLETYPE))
CXXFLAGS+=$(CODITYPE)
all:$(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)

