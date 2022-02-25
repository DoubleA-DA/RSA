#include"bits/stdc++.h"
using namespace std;
///////////////////Generate all path with random bandwidth
void gen_path(int l,string dir1)
{
   //string dir=getenv("HOME");
   string dir=dir1+"/Documents/RSA/data2.txt";
   fstream f1(dir,ios_base::app);
   //fstream f1("C:\\Users\\user\\Downloads\\data2.txt",ios_base::app);
   for(int i=0;i<l;i++)
   {
      for(int j=0;j<l;j++)
      {
         if(i==j)continue;
         f1<<i<<" "<<j<<" "<<rand()%400+1<<"\n";
      }
   }
   f1.close();
}