#include<bits/stdc++.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
 pid_t pid1=fork();
 if(pid1==0)
 {
  pid_t pid2=fork();
  if(pid2 == 0)
  {
   int c=execl("./division","division","100","50", NULL);
   if(c==-1)
   {
    perror("error!\n");
   }
  }
  else
  {
   wait(NULL);
   int c=execl("./multiply","multiply","100","50", NULL);
   if(c==-1)
   {
    perror("error!\n");
   }
  }
 }
 else
 {
  wait(NULL);
  pid_t pid3=fork();
  if(pid3 == 0)
  {
   int c=execl("./add","add","100","50", NULL);
   if(c==-1)
   {
    perror("error!\n");
   }

  }
  else
  {
   wait(NULL);
   int c=execl("./sub","sub","100","50", NULL);
   if(c==-1)
   {
    perror("error!\n");
   }
   
  }
 }
 return 0;
}
