#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<fstream>
#include<iostream>
#include <netinet/in.h>
using namespace std; 

#define PORT    6002
#define MAXLINE 1024
 
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;
     
    
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully\n");
     
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
     
   
    servaddr.sin_family    = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");		
    servaddr.sin_port = htons(PORT);
     
    
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket bind completed successfully\n");
    int len, n;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                (socklen_t*)&len);
    
    buffer[n] = '\0';
    FILE *outfile;
    outfile = fopen("file.txt", "w");
    
    if(outfile == NULL)
    	return 1;
    fwrite(buffer, sizeof(char), n, outfile);	
    
    fclose(outfile);
    printf("File Successfully received.\n"); 
    close(sockfd);
    return 0;
}
