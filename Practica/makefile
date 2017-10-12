SRC=./src
INC=./include
BIN=./bin
OBJ=./obj
LIB=./lib
ZIP=./zip

OPT=-Wall -g
PRJ=practica6

all: $(BIN)/testimagen $(BIN)/testarteASCII $(BIN)/testplano $(BIN)/testMorphing

$(BIN)/testimagen: $(OBJ)/testimagen.o $(LIB)/libimagen.a
	g++ -o $@ $< -limagen -L$(LIB)

$(BIN)/testplano: $(OBJ)/testplano.o $(LIB)/libimagen.a
	g++ -o $@ $< -limagen -L$(LIB)

$(BIN)/testarteASCII: $(OBJ)/testarteASCII.o $(LIB)/libimagen.a
	g++ -o $@ $< -limagen -L$(LIB)

$(BIN)/testMorphing: $(OBJ)/testMorphing.o $(LIB)/libimagen.a
	g++ -o $@ $< -limagen -L$(LIB)

$(OBJ)/testimagen.o: $(SRC)/testimagen.cpp $(INC)/imagen.h $(INC)/byte.h
	g++ $(OPT) -c $< -o $@ -I$(INC)

$(OBJ)/testplano.o : $(SRC)/testplano.cpp $(INC)/imagen.h $(INC)/byte.h
	g++ $(OPT) -c $< -o $@ -I$(INC)

$(OBJ)/testarteASCII.o : $(SRC)/testarteASCII.cpp $(INC)/imagen.h $(INC)/byte.h
	g++ $(OPT) -c $< -o $@ -I$(INC)

$(OBJ)/testMorphing.o : $(SRC)/testMorphing.cpp $(INC)/imagen.h $(INC)/lista.h $(INC)/byte.h
	g++ $(OPT) -c $< -o $@ -I$(INC)

$(LIB)/libimagen.a : $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/byte.o $(OBJ)/lista.o 
	ar -rvs $@ $^

$(OBJ)/lista.o: $(SRC)/lista.cpp  $(INC)/imagen.h $(INC)/lista.h 
	g++ $(OPT) -c $< -o $@ -I$(INC)

$(OBJ)/imagen.o : $(SRC)/imagen.cpp $(INC)/imagen.h $(INC)/byte.h $(INC)/pgm.h
	g++ $(OPT) -c $< -o $@ -I$(INC)

$(OBJ)/pgm.o : $(SRC)/pgm.cpp $(INC)/pgm.h
	g++ $(OPT) -c $< -o $@ -I$(INC)

$(OBJ)/byte.o : $(SRC)/byte.cpp $(INC)/byte.h
	g++ $(OPT) -c $< -o $@ -I$(INC) 

clean: 
	rm -f $(OBJ)/*.o $(BIN)/* $(LIB)/* $(ZIP)/*
	
zip: clean
	zip -r $(ZIP)/$(PRJ).zip *

