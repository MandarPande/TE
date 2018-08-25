#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string>

#define LPORT 6002
#define MAXLINE 1024

int main(int argc, char *argv[])
{
	int sockfd;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr;
	
	//char *hello = new char[100];
	
	/*char *hello;
	ifstream infile;
	infile.open("file.txt");
	infile >> infile;
	*/
	FILE *infile;
	char* msg;
	long numbytes;
	
	infile = fopen("file.txt","r");
	if(infile == NULL)
	{
		return 1;
	}
	
	fseek(infile, 0L, SEEK_END);
	numbytes = ftell(infile);
	//printf("%ld", numbytes);
	fseek(infile, 0L, SEEK_SET);
	msg = (char*)calloc(numbytes, sizeof(char));
	//printf("%ld", sizeof(msg));
	if(msg== NULL)
	{
		return 1;
	}
	
	fread(msg, sizeof(char), numbytes, infile);
	
	
	fclose(infile);
	
	
	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0 )
	{
		perror("Socket Creation Failed\n");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
   	servaddr.sin_port = htons(LPORT);
    	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    	//memset(servaddr.sin_zero, '\0', sizeof(servaddr.sin_zero));  
    	printf("Socket created successfully\n");
    	int n,len;
     
   	sendto(sockfd, (const char *)msg, strlen(msg),
                       MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
                       sizeof(servaddr));
         
    	
   	printf("File successfully Transferred\n");
 	
    	close(sockfd);
	return 0;
}

