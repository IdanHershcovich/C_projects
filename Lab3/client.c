#include "csapp.c"
#include "csapp.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

char * constructRequest(char *host,char *file)
{
	static char buff[MAXLINE];
	sprintf(buff, "GET /%s HTTP/1.1\r\nHost: %s \r\n", file, host);
	sprintf(buff, "%s\r\n", buff);
	printf("%s", buff);
	return buff;

}

int main (int argc, char * * argv) 
 {
	int clientfd, port;
	char *host, buf[MAXLINE], *file, *request_buf;
	rio_t rio;

	if (argc != 4) 
	{
		fprintf(stderr, "usage: %s <host> <port> <file>\n", argv[0]);
		exit(0);
	}
	host = argv[1];
	port = atoi(argv[2]);
	file = argv[3];
	request_buf=constructRequest(host,file);
	strcpy(buf, request_buf);
	
	clientfd = Open_clientfd(host, port);
	Rio_readinitb(&rio, clientfd);
  	
		Rio_writen(clientfd, buf, strlen(buf));
		while(Rio_readnb(&rio, buf, MAXLINE) !=0)
		{
			printf( "%s", buf);
		}

  Close(clientfd);
  exit(0);
 }