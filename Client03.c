// A simple test client to connect to server
// A simple test client
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<time.h>


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n,i,g;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char f;
    char buffer1[20];
    char buffer2[20];

    // Set buffer memory
	memset(buffer1,' ',20);
	memset(buffer2,' ',20);

	time_t now;
	time(&now);

	printf("\n\n%s\n\n",ctime(&now));

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){ 
        error("ERROR opening socket");
        exit(1);
    }
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
    (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
        exit(1);
    }

    if(fork())
	{
        printf("\nEnter the data to be send type exit for stop:\n");
        scanf("%s",buffer1);
		while(strcmp(buffer1,"exit")!=0)
        {
            send(sockfd,buffer1,20,0);
		memset(buffer1,' ',20);
		gets(buffer1);
		
        
    	}
		send(sockfd,"exit",5,0);
	}
    else 
    {
        memset(buffer2,' ',20);
        i=recv(sockfd,buffer2,20,0);
		buffer2[20]='\n';
        while(strcmp(buffer2,"exit")!=0)
        {
		i=recv(sockfd,buffer2,20,0);
                printf("\n%s",buffer2);
		memset(buffer2,' ',20);
		}
        send(sockfd,"exit",5,0);
    }
    close(sockfd);
    return 0;
}
