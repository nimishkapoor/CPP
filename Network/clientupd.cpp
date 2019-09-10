#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int sock;
	sock=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server,client;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5555);
	bind(sock,(struct sockaddr*)&server,sizeof(server));
	char buf[1024];
	sendto(sock,"YEAH YEAH",1024,0,(struct sockaddr*)&client,sizeof(client));
	socklen_t clientlen=sizeof(client);
	recvfrom(sock,buf,100,0,(struct sockaddr*)&client,&clientlen);
	return 0;
}
