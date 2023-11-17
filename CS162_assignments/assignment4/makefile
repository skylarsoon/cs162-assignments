CC = g++ -std=c++11 -g
exe_file = run

$(exe_file): driver.cpp game.o room.o event.o wumpus.o gold.o bats.o pit.o 
	$(CC) driver.cpp game.o room.o wumpus.o gold.o bats.o pit.o -o $(exe_file)

game.o: game.h game.cpp
	$(CC) -c game.cpp

room.o: room.h room.cpp
	$(CC) -c room.cpp

event.o: event.h

wumpus.o: wumpus.h wumpus.cpp
	$(CC) -c wumpus.cpp

gold.o: gold.h gold.cpp
	$(CC) -c gold.cpp

bats.o: bats.h bats.cpp
	$(CC) -c bats.cpp

pit.o: pit.h pit.cpp
	$(CC) -c pit.cpp