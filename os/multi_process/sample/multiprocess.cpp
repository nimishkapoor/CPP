#include<unistd.h>
#include<bits/stdc++.h>
using namespace std;
int main()
{
 pid_t status;
 status=fork();
 if(status==0)
 {
  for(int i=0;i<100;i++)
  {
   cout<<i<<endl;
  }
 }
 else if (status>0)
 {
  for(int i=99;i<200;i++)
  {
   cout<<i<<endl;
  }
 }
 cout<<"terminating"<<endl;
 return 0;
}
