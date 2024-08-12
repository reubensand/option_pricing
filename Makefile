CC=g++ -std=c++11 -g
EXE_FILE=fin

all: $(EXE_FILE)


$(EXE_FILE): black_scholes.o binomial.o main.o
	$(CC) black_scholes.o binomial.o main.o  -o $(EXE_FILE)

black_scholes.o: black_scholes.cpp
	$(CC) -c black_scholes.cpp

binomial.o: binomial.cpp
	$(CC) -c binomial.cpp

main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm -f *.o $(EXE_FILE)
