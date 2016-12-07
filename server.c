#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>

int main(int argc,char *argv[])
{

int sockfd,port_no,clilen,n,newsockfd;
struct sockaddr_in servr_addr,cli_addr;
char buffer[256];

//create socket
sockfd = socket(AF_INET,SOCK_STREAM,0);


if(sockfd<0){
	perror("error opening socket");
}


//initialize the socket variables
bzero((char*) &servr_addr,sizeof(servr_addr));
port_no = 5001;
servr_addr.sin_family = AF_INET;
servr_addr.sin_port = htons(port_no);
servr_addr.sin_addr.s_addr = INADDR_ANY;


//bind to socket

if(bind(sockfd,(struct sockaddr *) &servr_addr,sizeof(servr_addr))<0) {
	perror("error in binding");
}
 
//listen
listen(sockfd,5);

clilen = sizeof(cli_addr);

newsockfd = accept(sockfd,(struct sockaddr*) &cli_addr,&clilen);

if(newsockfd<0){
	perror("error in accepting");
}

bzero(buffer,256);
n =read(newsockfd,buffer,256);

if(n<0){
	perror("error in reading");
	exit(1);
}

printf("the message is %s",buffer);

n = write(newsockfd,"yes",3);
if(n<0){
	perror("error in writing");
	exit(1);
}


}