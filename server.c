
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>

#define PORT 9001

int main()
{
 int socketId;
 int client;
 struct sockaddr_in server;
 int addLen = sizeof(server);

 char fileName[1024] = {0}; 
 server.sin_family = AF_INET;
 server.sin_port = htons(PORT);
 server.sin_addr.s_addr = INADDR_ANY;
 
 socketId = socket(AF_INET, SOCK_STREAM, 0);
 int enable = 1;
if (setsockopt(socketId, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    printf("SO_REUSEADDR failed\n");
 
 bind(socketId, (struct sockaddr *)&server, sizeof(server));

 listen(socketId, 0);
 printf("Server up and running...\n");
 
 client = accept(socketId, (struct sockaddr *)&server, (socklen_t *)&addLen);
 
 printf("Client request accepted.\n");
 read(client, fileName, 1024);
 printf("Client : %s\n", fileName);

 FILE* file_;
 file_ = fopen(fileName,"r");
 if (file_ == NULL){
 	printf("FILE NOT FOUND\n");
 }else{
	 int count = 0;
	 while (!feof(file_)) //while EOF
	{ 
		char fileData[1024]={0};
	    fread(fileData, 1,1024, file_);  
	    write(client, fileData, sizeof(fileData));
	    count++;
	}
	printf("Chunks transmitted: %d\n", count);
	printf("File transfer successful.");
}
 close(socketId);
}