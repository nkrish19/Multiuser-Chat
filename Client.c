#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

void * doRecieving(void * sockID){

	int clientSocket = *((int *) sockID);

	while(1){

		char data[1024];
		int read = recv(clientSocket,data,1024,0);
		data[read] = '\0';
		printf("%s\n",data);

	}

}

int main(){

	int clientSocket = socket(AF_UNIX, SOCK_STREAM, 0);

	struct sockaddr_un serverAddr;

	serverAddr.sun_family = AF_UNIX;
	strcpy(serverAddr.sun_path, "socket_path");
    int len = strlen(serverAddr.sun_path) + sizeof(serverAddr.sun_family);

    //serverAddr.sin_port = htons(8080);
	//serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(connect(clientSocket, (struct sockaddr*) &serverAddr, len) == -1){
        perror("connect");
        exit(1);
    }

    char name[256];
    char form[] = "\n--From ";
    printf("Input Name\n");
    scanf("%s", name);

	printf("Connection established ............\n");

	pthread_t thread;
	pthread_create(&thread, NULL, doRecieving, (void *) &clientSocket );

	while(1){

		char input[1024];
		scanf("%s",input);

		if(strcmp(input,"LIST") == 0){

			send(clientSocket,input,1024,0);

		}
		else if(strcmp(input,"SEND") == 0){

			send(clientSocket,input,1024,0);
			
			scanf("%s",input);
			send(clientSocket,input,1024,0);
			
			scanf("%[^\n]s",input);
            strcat(form, name);
            strcat(input, form);
			send(clientSocket,input,1024,0);

            //send(clientSocket,name,1024,0);

		}
        else if (strcmp(input,"ALL") == 0){

            send(clientSocket,input,1024,0);
			
			//scanf("%s",input);
			//send(clientSocket,input,1024,0);
			
			scanf("%[^\n]s",input);
            strcat(form, name);
            strcat(input, form);
			send(clientSocket,input,1024,0); 

            //send(clientSocket,name,1024,0);           

        }
        else{
            
            //send(clientSocket,input,1024,0);
            printf("Invalid Syntax\n");

        }

	}


}