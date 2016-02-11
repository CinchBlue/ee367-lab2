CC="gcc"

server: server.o server_main.o
	gcc -o server server.o server_main.o 

server_main.o: server_main.c
	gcc -o server_main.o -c server_main.c

server.o: server.c
	gcc -o server.o -c server.c

clean:
	rm *.o
