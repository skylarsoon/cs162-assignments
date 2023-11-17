CC=g++ --std=c++11 -g
exe_file=run

$(exe_file): run_pokemon.cpp pokemon.o
	$(CC) run_pokemon.cpp pokemon.o -o $(exe_file)

pokemon.o: pokemon.h pokemon.cpp
	$(CC) -c pokemon.cpp

clean: 
	rm -f *.o $(exe_file)