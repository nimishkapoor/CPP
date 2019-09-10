#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include <stdio.h>
int main()
{
	int sock;
	struct sockaddr_in server,client;
	
	sock=socket(AF_INET,SOCK_DGRAM,0);
	
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5555);
	
	bind(sock,(struct sockaddr*)&server,sizeof(server));
	
	char buf[1024];
	while(1)
	{
		sendto(sock,buf,100,0,(struct sockaddr*)&client,sizeof(client));
		socklen_t clientlen=sizeof(client);
		recvfrom(sock,buf,100,0,(struct sockaddr*)&client,&clientlen);
	}
	
}
