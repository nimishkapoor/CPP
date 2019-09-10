#include<bits/stdc++.h>
using namespace std;
#include<pthread.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h> //for open
#include<unistd.h> //for close

char client_message[2000];
char buffer[1024];
pthread_mutex_t lock= PTHREAD_MUTEX_INITIALIZER;

void * socketProcess(int clientSocket)
{
	int newSocket = clientSocket;
	recv(newSocket,client_message,2000,0);
	
	//pthread_mutex_lock(&lock);
	char *message = (char*)malloc(sizeof(client_message)+20);
	strcpy(message,client_message);
	strcat(message,"\n");
	strcpy(buffer,message);
	//pthread_mutex_unlock(&lock);
	sleep(1);
	send(newSocket,buffer,13,0);
	printf("Exit socketProcess!\n");
	close(newSocket);
	//pthread_exit(NULL);
}



int main()
{
	int serverSocket, newSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	pid_t pid[50];
	
	//create the socket
	serverSocket = socket(PF_INET,SOCK_STREAM,0);
	
	//Configure settings of the server address struct;
	
	//Address family Internet
	serverAddr.sin_family=AF_INET;
	
	//set port number using htons function to use proper byte order
	serverAddr.sin_port=htons(7799);
	
	//set IP address to localhost
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//set all bits of padding field to zero
	memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);
	
	//Bind the address to the socket
	bind(serverSocket,(struct sockaddr*) &serverAddr, sizeof(serverAddr));
	
	//listen on the socket with 40 max connection request queued
	if(listen(serverSocket,50)==0)
	{
		printf("Listening\n");
	}
	else
	{
		printf("Error\n");
	}
	
	//pthread_t tid[60];
	int i=0;
	while(1)
	{
		//Accept callscreates a new socket for incoming connections
		addr_size=sizeof serverStorage;
		newSocket=accept(serverSocket,(struct sockaddr *) &serverStorage, &addr_size);
		//for each client request reates a thread and assign the client reqest to it to 
		//process so the main thread can entertain next request
		
		int pid_c=0;
		if((pid_c==fork())==0)
		{
			socketProcess(newSocket);
		}
		else
		{
			pid[i++]=pid_c;
			if(i>49)
			{
				i=0;
				while(i<50)
					waitpid(pid[i++],NULL,0);
				i=0;
			}
		}
		
	}
	return 0;
}
