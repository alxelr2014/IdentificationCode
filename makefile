CXX = g++
CXXFLAGS = -Wall -g
BUILDFLAGS = -lgmpxx -lgmp
RM = rm -f
INC = include/
OUT = out/
SRC = src/
TST = test/
BIN = bin/

SRC_MAINFUL = $(wildcard $(SRC)*.cpp)
SRC_MAINLESS = $(filter-out $(SRC)main.cpp, $(wildcard $(SRC)*.cpp))

SRC_OBJ = $(patsubst $(SRC)%.cpp, $(OUT)%.o ,$(SRC_MAINFUL))
SRC_MAINLESS_OBJ = $(patsubst $(SRC)%.cpp, $(OUT)%.o ,$(SRC_MAINLESS))
TST_OBJ = $(patsubst $(TST)%.cpp, $(OUT)$(TST)%.o ,$(wildcard $(TST)*.cpp))
TST_EXE = $(patsubst $(TST)%.cpp, $(BIN)$(TST)% ,$(wildcard $(TST)*.cpp))
run_main:
	$(BIN)main

runt_%: 
	$(BIN)$(TST)$*

main: $(SRC_OBJ) 
	$(CXX) $(CXXFLAGS) $^ -o $(BIN)$@ $(BUILDFLAGS)

test: $(TST_EXE)

$(BIN)$(TST)%: $(OUT)$(TST)%.o $(SRC_MAINLESS_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o  $@

$(OUT)%.o: $(SRC)%.cpp 
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(BUILDFLAGS)

$(OUT)$(TST)%.o: $(TST)%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ 

clean:
	$(RM) $(BIN)main $(SRC_OBJ) $(TST_OBJ) $(TST_EXE)