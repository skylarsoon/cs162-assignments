CC = g++ -std=c++11 -g
exe_file = run

$(exe_file): test_linked_list.cpp linked_list.o
	$(CC) test_linked_list.cpp linked_list.o -o $(exe_file)

linked_list.o: linked_list.h linked_list.cpp
	$(CC) -c linked_list.cpp

clean:
	rm -f *.o $(exe_file)