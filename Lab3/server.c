#include "csapp.c"
#include "csapp.h"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//Function that takes in the parsed filename and the active socket and writes to client
int writeFile(char *file, int sckt)
{
	int fd  = open(file, O_RDONLY, 0);
	int read_bytes;
	static char buf[MAXLINE];

	rio_t rio;
	Rio_readinitb(&rio, fd);
	
	//File not found: 404
	if (fd < 0)
	{   
		printf("Client request file not found!\n");
		Rio_writen(sckt, "HTTP/1.1 404 Not Found \nContent-Length: 0 \r\n\r\n", 42); //write to client
		return -1;
	}

	// Read from the file to the buffer
	while((read_bytes = Rio_readlineb(&rio, buf, MAXLINE)))
	{
		//Write the contents of the buffer to the client
		Rio_writen(sckt, buf, strlen(buf)); //write to client
	}

	if(read_bytes == 0)
	{
		printf("------------------File: %s sent to client -------------------\n", file);
	}
	
	Close(fd);
	return 0;
}

//Function that opens the socket and listens for connections
void serve(int port)
{
	//Initializing socket and rio vars
	int server_fd, new_socket; 
    struct sockaddr_in address;
    int addrlen = sizeof(address);
	rio_t rio;
	Rio_readinitb(&rio, server_fd);  
	server_fd = Socket(AF_INET, SOCK_STREAM, 0);

	//setting the struct values
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htons(INADDR_ANY);
    address.sin_port = htons( (unsigned short) port );
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
	//bind function to associate socket address with descriptor
   	Bind(server_fd, (struct sockaddr *)&address, sizeof(address));
 
	//listen for server connections
	listen(server_fd, 5);

	//while loop to keep the server going
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");

		//Accept any connection
        new_socket = Accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        Rio_readinitb(&rio, new_socket);  
	
		//vars to parse the client request and get the file name
        char *token_http, *token_file, *response, token_buf[MAXLINE], buffer[MAXLINE];

		//read the client request, copy it to a token
        Rio_readlineb( &rio , buffer, MAXLINE);
		strcpy(token_buf, buffer);

        printf("%s\n",token_buf );

		//parse
		token_http = strtok(token_buf, "/");
		token_file = strtok(NULL, " ");

		//call function to write back to client
		writeFile(token_file, new_socket);        
        close(new_socket);
    }
}

int main(int argc, char const *argv[])
{
    int port; 
        
	if (argc != 2) 
	{
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}

	//set port to command line argument 
  	port = atoi(argv[1]);

	serve(port);
    
}