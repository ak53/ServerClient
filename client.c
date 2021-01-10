#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

#define PORT 9001

int main(){
 int sock = 0;
 struct sockaddr_in server;
 char fileNameToSend[1024];
 char recBuff[1024];
 
 server.sin_family = AF_INET;     
 server.sin_port = htons(PORT);   
 server.sin_addr.s_addr = INADDR_ANY;   //connects socket to all interfaces

 sock = socket(AF_INET, SOCK_STREAM, 0);
 connect(sock, (struct sockaddr * )&server, sizeof(server));
 printf("Connected to server\n");
 
 printf("Enter the name of required file with extension\n");
 scanf("%s", &fileNameToSend); 
 send(sock, fileNameToSend, strlen(fileNameToSend), 0);
 
printf("Receiving packets\n"); 
char newName[1024] = "received_";
strcat(newName,fileNameToSend);

int bytesReceived;
FILE *fp;
fp=fopen(newName,"w");
int count=0;
while((bytesReceived = read(sock,recBuff,1024))>0){
	fwrite(recBuff,1,bytesReceived,fp);
	count++;
}
printf("Received chunks: %d\n", count);
fclose(fp); 
 printf("Closing socket\n");
 close(sock);
}
