CC=g++ --std=c++11 -g
exe_file=run

$(exe_file): shop.o menu.o order.o coffee.o prog.o
	$(CC) shop.cpp menu.cpp order.cpp coffee.cpp prog.cpp -o $(exe_file)

coffee.o: coffee.h coffee.cpp
	$(CC) -c coffee.cpp
shop.o: shop.h shop.cpp
	$(CC) -c shop.cpp
menu.o: menu.h menu.cpp
	$(CC) -c menu.cpp
order.o: order.h order.cpp
	$(CC) -c order.cpp

clean: 
	rm -f *.o $(exe_file)