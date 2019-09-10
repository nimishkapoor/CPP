#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
int main()
{
	int sock,newsock;
	
	struct sockaddr_in server,client;
	
	sock=socket(AF_INET,SOCK_STREAM,0);
	
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5555);
	
	bind(sock,(struct sockaddr *)&server,sizeof(server));
	
	listen(sock,5);
	
	char buffer[1024];
	
	socklen_t len=sizeof(client);
	while(1)
	{
		newsock=accept(sock, (struct sockaddr *)&client, &len);
		int childpid;
		if((childpid=fork())==0)
		{
			close(sock);
			read(newsock,buffer,1024);
			cout<<buffer<<endl;
			write(newsock,"Yeah Yeah",9);
			//exit(0);
		}
		close(newsock);
	}
	
	
}
