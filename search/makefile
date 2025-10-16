CC = g++
default: searchengine clean
searchengine: searchengine.o Readinput.o
	$(CC) -o searchengine searchengine.o Readinput.o
Readinput.o: Readinput.cpp Readinput.h
	$(CC) -o Readinput.cpp
searchengine.o: searchengine.cpp searchengine.h
	$(CC) -c searchengine.cpp

clean:
	rm *.o