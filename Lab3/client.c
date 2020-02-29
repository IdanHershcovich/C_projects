#include "csapp.c"
#include "csapp.h"
#include <stdio.h>
#include <string.h>


//Function to create the correctly formatted header.
char * constructRequest(char *host,char *file)
{
	static char buf[MAXLINE];
	sprintf(buf, "GET %s HTTP/1.1\r\n", file);
	sprintf(buf, "%sHost: %s\r\n", buf, host);
	sprintf(buf, "%s\r\n", buf);
	printf("%s", buf);
	return buf;
}

int main (int argc, char * * argv) 
 {
	//initializing variables
	int clientfd, port;
	char *host, buf[MAXLINE], *file, *request_buf;
	rio_t rio;

	//Usage for the program
	if (argc != 4) 
	{
		fprintf(stderr, "usage: %s <host> <port> <file>\n", argv[0]);
		exit(0);
	}

	//Assigning command line arguments to variables
	host = argv[1];
	port = atoi(argv[2]);
	file = argv[3];

	//the constructed header
	request_buf=constructRequest(host,file);
	strcpy(buf, request_buf);
	
	//Open the client and initializes the rio ptr to that client
	clientfd = Open_clientfd(host, port);
	Rio_readinitb(&rio, clientfd);
  	
	//Send the header request in buf to the server
	Rio_writen(clientfd, buf, strlen(buf));

	//Print out whatever the server sends back
	while(Rio_readlineb(&rio, buf, MAXLINE))
	{
		char *stop= "</html>";
		printf( "%s", buf);
		if(strstr(buf,stop)) break;
	}


  Close(clientfd);
  exit(0);
 }