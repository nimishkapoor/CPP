#include<bits/stdc++.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
 pid_t child=fork();
 if(child < 0)
 {
  perror("fork()error");
  exit(-1);
 }
 if(child != 0)
 {
  printf("I'm the parent  %d, mychild is %d\n",getpid(),child);
  wait(NULL);
 }
 else
 {
  printf("I'm the child %d, my parent is %d\n",getpid(),getppid());
  execl("/bin/echo","echo","Hello, World", NULL);
 }
 return 0;
}
