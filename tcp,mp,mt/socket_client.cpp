#include<bits/stdc++.h>
using namespace std;
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<fcntl.h> //for open
#include<unistd.h> //for close
#include<pthread.h>

void * clientThread(void *arg)
{
	printf("InThread.\n");
	char message[1000];
	char buffer[1024];
	int clientSocket;
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	
	//create the socket
	clientSocket=socket(PF_INET,SOCK_STREAM,0);
	//Configure settings of the server address
	//Address family is Internet
	serverAddr.sin_family=AF_INET;
	//set port number using hton function
	serverAddr.sin_port = htons(7799);
	
	//Set IP address to localhost
	serverAddr.sin_addr.s_addr=inet_addr("localhost");
	
	memset(serverAddr.sin_zero,'\0',sizeof(serverAddr.sin_zero));
	
	//connect the socket to the server using he address
	addr_size = sizeof serverAddr;
	connect(clientSocket,(struct sockaddr *) &serverAddr,addr_size);
	strcpy(message,"Hello");
	
	if(send(clientSocket,message,strlen(message),0)<0)
	{
		printf("Send failed\n");
	}
	//Read the message from server into the buffer 
	if(recv(clientSocket,buffer,1024,0)<0)
	{
		printf("Recieve Failed\n");
	}
	//print the recieved message
	printf("Data recieved: %s\n",buffer);
	close(clientSocket);
	pthread_exit(NULL);
}
int main()
{
	int i=0;
	pthread_t tid[51];
	while(i<50)
	{
		if(pthread_create(&tid[i],NULL,clientThread,NULL)!=0)
		{
			printf("Failed to create thread\n");
		}
		i++;
	}
	sleep(20);
	i=0;
	while(i<50)
	{
		pthread_join(tid[i++],NULL);
		printf("%d:\n",i);
	}
	return 0;
}
