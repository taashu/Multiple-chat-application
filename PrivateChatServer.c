/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include<netdb.h>
#include<time.h>
#include<fcntl.h>
#include<sys/stat.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// Provide host name and port for server while starting.

int main(int argc, char *argv[])
	{
	int nsd1,nsd;
	
	char connectedClientname[5];
	int sockfd, portno,i,j,p,g,m,no;
    	socklen_t clilen;
	char e;
        char buffer1[20];
	char buffer2[20];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
        int fp;

	memset(buffer1,' ',20);
	memset(buffer2,' ',20);
	if (argc < 2) 
	{
         fprintf(stderr,"ERROR, Please provide no port provided\n");
         exit(1);
	}
     
       sockfd = socket(AF_INET, SOCK_STREAM, 0);
       if (sockfd < 0) 
        error("ERROR opening socket");
        
        
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     
     time_t now;
     time (&now);

     printf("\n\n%s\n\n",ctime(&now));

     fp = open("/home/neha/LogPrivate.txt",O_CREAT|O_RDWR|O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
     
     if(fp==-1)
	printf("ERROR OPEN\n");     
     
     write(fp,"Details of Server Running",26);
     write(fp,"\n\n",1);
     write(fp,ctime(&now),30);
     write(fp,"\n\n",1);
     
     // Server listens for the request on the given host and port and 
     // as request is recieved , it forks a process that creates the socket and 
     // go back to listening again.
     while(1)
	{	
		//private chat code -->
       		
		nsd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
		
		nsd1 = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
      		if (nsd < 0) 
		{
	         	 error("ERROR on accept of 1");
	        }
		if (nsd1 < 0) 
		{
	         	 error("ERROR on accept of 2");
	        }
		
		
     		
      		//printf("\nConnection accepted! with client named : %c", connectedClientname[p]);
		
		//char c[50] = "hi i am server.what is ur name";
			     	
		//write(nsd, c, strlen(c)); 
		//write(nsd1, c, strlen(c)); 

      // Create a process that handles this 


	//      int process = fork();
	  //    if(process > 0)
		//{
	

//PRIVATE CHAT IMPLeMENTATION
		if(fork())
    		{
        		        	
			i = recv( nsd1,buffer1,20,0);
			
	    		while(strcmp(buffer1,"exit")!=0)
	    		{	
				send(nsd, buffer1, strlen(buffer1),0);
				
 				write(fp,"CLIENT 1 : ",12);
		 		write(fp,buffer1,strlen(buffer1));
		 		write(fp,"\n",1);
				memset(buffer1,' ',20);

				i=recv(nsd1,buffer1,20,0);
	        		
	    		}
   
         
      		} 
	else 
		{


		        	
			i = recv( nsd,buffer2,20,0);
			
	    		while(strcmp(buffer2,"exit")!=0)
		 	{		
				send(nsd1, buffer2, strlen(buffer2),0);
				
				write(fp,"CLIENT 2 : ",12);
		 		write(fp,buffer2,strlen(buffer2));
		 		write(fp,"\n\n",1);
				memset(buffer2,' ',20);	  

				i=recv(nsd,buffer2,20,0);      		
				
	    		}





		}
	
    }
	    printf("\nBye");
	    send(nsd1,"Offline",10,0);
	 send(nsd,"Offline",10,0);
	
	
	    close(sockfd);
	    close(nsd1);
	    close(nsd);
	



	    return 0;
}
