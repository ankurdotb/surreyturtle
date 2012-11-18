# simple C++ makefile

CC=g++

GLLIB=-lGL -lglut -lGLU   -lm

PROGNAME=shape

PROG=$(PROGNAME)
OBJ=$(PROGNAME).o
SRC=$(PROGNAME).cpp

$(PROG): $(OBJ)
	 $(CC) $(OBJ) $(GLLIB) -o $(PROG)

$(OBJ): $(SRC)
	 $(CC) -c $(SRC)

clean: 
	/bin/rm -rf $(OBJ) $(PROG)


