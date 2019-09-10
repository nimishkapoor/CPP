#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int sock;
	struct sockaddr_in server;
	sock=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5555);
	connect(sock,(struct sockaddr*)&server,sizeof(server));
	char buf[1024];
	while(1)
	{
		write(sock,"OH YEAH",9);
		read(sock,buf,1024);
		cout<<buf<<endl;
	}
	close(sock);
}
