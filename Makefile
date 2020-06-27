CC = g++
LIBS = -lncurses
TARGET = Snakegame

$(TARGET) : main3.o snakere.o
	$(CC) -W -Wall -o $(TARGET) main3.o snakere.o -std=c++11 $(LIBS)

main3.o : main3.cpp
	$(CC) -W -Wall -c -o main3.o main3.cpp -std=c++11 $(LIBS)
snakere.o : snakere.cpp
	$(CC) -W -Wall -c -o snakere.o snakere.cpp -std=c++11 $(LIBS)
clean:
	rm -rf *.o
