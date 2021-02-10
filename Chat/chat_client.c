#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 1024 
#define SIZE 4096
int main(int argc, char const *argv[]) 
{ 
	struct sockaddr_in address; 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char *hello = "Hi there this is client side"; 
	char buffer[SIZE]; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	// This binds the client to localhost 
	/*if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} */

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	while(1)
	{
		
		printf("CLIENT: ");
		gets(buffer);
		send(sock, buffer, SIZE, 0);
		read(sock, buffer, SIZE);
		printf("SERVER: %s\n", buffer);
		if(strcmp(buffer, "bye") == 0)
			break;

	}
	return 0; 
} 
