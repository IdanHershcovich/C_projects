/* 
* echoserveri.c - An iterative echo server 
*/ 
#include "csapp.h"

#define BUFMAX 1024

void echofile(int connfd)
{
   int data, filefd;
   char buf[BUFMAX];

   data = read(connfd, buf, BUFMAX);
   printf("%s", buf);
   filefd = open("Makefile", O_RDONLY);
   if(filefd < 0){
  	write(connfd, "Couldn't Open file\n", 19);
   }
   while(1){
  	data = read(filefd, buf, BUFMAX);

  	int status = data;
  	if(status == 0){
     	break;
  	}

  	data = write(connfd, buf, status);
   }
   close(filefd);
}

int main(int argc, char **argv) 
 {
  int listenfd, connfd, port, clientlen;
  struct sockaddr_in clientaddr;
  struct hostent *hp;
  char *haddrp;
  if (argc != 2) 
   {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
   }
  port = atoi(argv[1]);

  listenfd = Open_listenfd(port);
  while (1) 
   {
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

	/* determine the domain name and IP address of the client */
	hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
	sizeof(clientaddr.sin_addr.s_addr), AF_INET);
	haddrp = inet_ntoal(clientaddr.sin_addr);
	printf("Server connected to %s (%s)\n", hp->h_name, haddrp);

	echofile(connfd);
	close(connfd);
   }
   
   exit(0);
 }
