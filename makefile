CXX = g++
CXXFLAGS = -Wall -g
RM = rm -f
HDR = include/
OBJ = object/
SRC = src/

run :
	./main
build: Main
cbuild: clean Main 
Main: $(OBJ)main.o $(OBJ)channel.o $(OBJ)codes.o $(OBJ)functions.o $(OBJ)identification.o $(OBJ)simulate.o $(OBJ)transmission.o $(OBJ)rando.o 
	$(CXX) $(CXXFLAGS)  $(OBJ)main.o $(OBJ)channel.o  $(OBJ)codes.o $(OBJ)functions.o $(OBJ)identification.o $(OBJ)simulate.o $(OBJ)transmission.o $(OBJ)rando.o -o main 

$(OBJ)%.o: $(SRC)%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	$(RM) main $(OBJ)main.o $(OBJ)channel.o $(OBJ)codes.o $(OBJ)functions.o $(OBJ)identification.o $(OBJ)simulate.o $(OBJ)transmission.o $(OBJ)rando.o