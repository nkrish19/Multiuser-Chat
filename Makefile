all:	Client Server

Client: Client.c
	gcc -o Client Client.c -pthread

Server: Server.c
	gcc -o Server Server.c -pthread
