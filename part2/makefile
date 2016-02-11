CC="gcc"

# server
server: server.o server_main.o
	gcc -o server server.o server_main.o 

server_main.o: server_main.c
	gcc -o server_main.o -c server_main.c

server.o: server.c
	gcc -o server.o -c server.c



# client
client: client.o client_main.o
	gcc -o client client.o client_main.o

client.o: client.c
	gcc -o client.o -c client.c

client_main.o: client_main.c
	gcc -o client_main.o -c client_main.c









clean:
	rm *.o
