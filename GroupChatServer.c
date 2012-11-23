#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>


struct sockaddr_in serv_addr, cli_addr;
char buffer1[20],buffer2[20],buffer3[20], buffer4[20], buffer5[20];
int nsd1,nsd2,nsd3,nsd4,nsd5 ;
 
 void error(const char *msg)
{
    perror(msg);
    exit(1);
}


// Handler for 3 clients
int handleThreeClients()
	{
	    int i;
		printf("Got 3 clients chat");
		if(fork()==0)
    		{
			i = recv( nsd1,buffer1,20,0);
			// Clients should type exit to close chat
			while(strcmp(buffer1,"exit")!=0)
	    		{	
					send(nsd2, buffer1, strlen(buffer1),0);
					send(nsd3, buffer1, strlen(buffer1),0);
	        		memset(buffer1,' ',20);
   					i=recv(nsd1,buffer1,20,0);
	    		}
      		} 
	
		else if(fork()>0)
		{
			i = recv( nsd3,buffer3,20,0);
			while(strcmp(buffer3,"exit")!=0)
		 	{		
				send(nsd2, buffer3, strlen(buffer3),0);
				send(nsd1, buffer3, strlen(buffer3),0);
	        	memset(buffer3,' ',20);	        		
				i=recv(nsd3,buffer3,20,0);
	    	}
	    }

 		else if(fork())
		{
 			i = recv( nsd2,buffer2,20,0);
		 	while(strcmp(buffer2,"exit")!=0)
			 	{		
					 send(nsd1, buffer2, strlen(buffer2),0);
					 send(nsd3, buffer2, strlen(buffer2),0);
		        	 memset(buffer2,' ',20);	        		
					i=recv(nsd2,buffer2,20,0);
		     	}
		}
	   }


// Handler for 4 clients
int handleFourClients()
	{ 
	 int i;
	 if(fork()==0)     {
     	i = recv( nsd1,buffer1,20,0);
     	while(strcmp(buffer1,"exit")!=0)
			{	
				 send(nsd3, buffer1, strlen(buffer1),0);
				send(nsd4, buffer1, strlen(buffer1),0);
				send(nsd2, buffer1, strlen(buffer1),0);
	        		//printf("\n Client1: %s\n",buffer1);
				memset(buffer1,' ',20);
	        		i=recv(nsd1,buffer1,20,0);
			}
   	}
    else if(fork()>0)
	{
		i = recv( nsd2,buffer2,20,0);
		while(strcmp(buffer2,"exit")!=0)
			{		
					 send(nsd1, buffer2, strlen(buffer2),0);
					send(nsd3, buffer2, strlen(buffer2),0);
	        		send(nsd4, buffer2, strlen(buffer2),0);
					//printf("\nClient2: %s\n",buffer2);
					memset(buffer2,' ',20);	        		
					i=recv(nsd2,buffer2,20,0);
			}
	}
	else 
	{
		int f1=fork();
		if(f1){
			i = recv( nsd3,buffer3,20,0);
			while(strcmp(buffer3,"exit")!=0)
		 			{		
						 send(nsd1, buffer3, strlen(buffer3),0);
						send(nsd2, buffer3, strlen(buffer3),0);
	        				send(nsd4, buffer3, strlen(buffer3),0);
						memset(buffer3,' ',20);	        		
						i=recv(nsd3,buffer3,20,0);
	    			}
		}
		else if (f1==0)
		{
			i = recv( nsd4,buffer4,20,0);
			while(strcmp(buffer4,"exit")!=0)
			 	{		
						 send(nsd1, buffer4, strlen(buffer4),0);
						send(nsd2, buffer4, strlen(buffer4),0);
	        				send(nsd3, buffer4, strlen(buffer4),0);
						memset(buffer4,' ',20);	        		
						i=recv(nsd4,buffer4,20,0);
	    		}

		}
	}
}



// Handle for 5 clients	
int handleFiveClients()
	{
	 int i;
	 if(fork()==0)	{
        		        	
			i = recv( nsd1,buffer5,20,0);
			while(strcmp(buffer5,"exit")!=0)
	    		{	
				 send(nsd2, buffer5, strlen(buffer5),0);
				send(nsd3, buffer5, strlen(buffer5),0);
				send(nsd4, buffer5, strlen(buffer5),0);
				send(nsd5, buffer5, strlen(buffer5),0);
	        		//printf("\n Client1: %s\n",buffer5);
				memset(buffer5,' ',20);
	        		i=recv(nsd1,buffer5,20,0);
	    		}
   
        	int f2=fork();

 			if(f2==0)
			{
	
				i = recv( nsd2,buffer5,20,0);
			
	    			while(strcmp(buffer5,"exit")!=0)
		 			{		
					 send(nsd1, buffer5, strlen(buffer5),0);
					send(nsd3, buffer5, strlen(buffer5),0);
		        		send(nsd4, buffer5, strlen(buffer5),0);
					send(nsd5, buffer5, strlen(buffer5),0);					
					//printf("\nClient2: %s\n",buffer2);
					memset(buffer5,' ',20);	        		
					i=recv(nsd2,buffer5,20,0);
	    			}
			}

			int f3=fork();
			if(f3==0)
			{

 						
	
				i = recv( nsd3,buffer5,20,0);
			
	    			while(strcmp(buffer5,"exit")!=0)
		 		{		
					 send(nsd1, buffer5, strlen(buffer5),0);
					send(nsd2, buffer5, strlen(buffer5),0);
	        			send(nsd4, buffer5, strlen(buffer5),0);
					send(nsd5, buffer5, strlen(buffer5),0);					
					//printf("\nClient2: %s\n",buffer5);
					memset(buffer5,' ',20);	        		
					i=recv(nsd3,buffer5,20,0);
	    			}

	        }
		
			int f4=fork();
			if(f4==0)
			{


			i = recv( nsd4,buffer5,20,0);
			
	    			while(strcmp(buffer5,"exit")!=0)
		 		{		
					 send(nsd1, buffer5, strlen(buffer5),0);
					send(nsd2, buffer5, strlen(buffer5),0);
	        			send(nsd3, buffer5, strlen(buffer5),0);
					send(nsd5, buffer5, strlen(buffer5),0);					
					//printf("\nClient2: %s\n",buffer5);
					memset(buffer5,' ',20);	        		
					i=recv(nsd4,buffer5,20,0);
	    			}
			}

      	} 
	
		else 
		{
			i = recv( nsd5,buffer5,20,0);
			while(strcmp(buffer5,"exit")!=0)
			 	{		
					 send(nsd2, buffer5, strlen(buffer5),0);
					send(nsd3, buffer5, strlen(buffer5),0);
	        			send(nsd1, buffer5, strlen(buffer5),0);
					send(nsd4, buffer5, strlen(buffer5),0);
					//printf("\nClient2: %s\n",buffer5);
					memset(buffer5,' ',20);	        		
					i=recv(nsd5,buffer5,20,0);
	    		}
		}
}

// Main program to initiate the server;
int main(int argc, char *argv[])
{
	// Allocate memory to buffers to be used  to receive data in sockets.
	memset(buffer1,' ',20);
	memset(buffer2,' ',20);
	memset(buffer3,' ',20);
	memset(buffer4,' ',20);
	memset(buffer1,' ',20);
	
     if (argc < 2) {
         fprintf(stderr,"ERROR, No server port provided\n");
         exit(1);
     }
     
     int sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
        
        
     bzero((char *) &serv_addr, sizeof(serv_addr));
     int portNumber = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portNumber);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
              error("ERROR on binding");
     }
     listen(sockfd,5);
     socklen_t clilen = sizeof(cli_addr); 
     int noOfClients ;
     while(1)
	  {	//assuming just 5 clients are to be accepted not more	
		printf("Welcome to group chat.Enter the number of chat buddies(Either 3,4 or 5):\n");
		scanf("%d",&noOfClients);
		if(noOfClients==3)
		{
       		nsd1 = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
			nsd2 = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
			nsd3 = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
		}
		else if(noOfClients==4)
		{
  			nsd1 = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
			nsd2 = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
			nsd3 = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
			nsd4=accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
		}
		else if(noOfClients==5)
		{
			nsd1 = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
			nsd2 = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
			nsd3 = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
			nsd4=accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
			nsd5 = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);     
		}
		else return -1;		 	
		if (nsd5< 0) {
			error("ERROR on accept");
		}
 	
		switch(noOfClients) 
		{
	    case 3:
	        handleThreeClients();
	        break;
	    case 4 :
	        handleFourClients();
	        break;
	    case 5 :
	        handleFiveClients();
	        break;
	   	default : 
		printf("Invalid entry"); 
	   }
	}

	// Any ctrl C signal to stop , close all sockets.
    printf("\nBye");
	send(nsd1,"Offline",10,0);
	send(nsd2,"Offline",10,0);
	send(nsd3,"Offline",10,0);
	send(nsd4,"Offline",10,0);
	send(nsd5,"Offline",10,0);
	
	close(sockfd);
	close(nsd1);
	close(nsd2);
	close(nsd3);
	close(nsd4);
	close(nsd5);

	    return 0;
}
