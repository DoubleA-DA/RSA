#include"bits/stdc++.h"
using namespace std;
////////////Creating Graph
void add(vector<pair<int,int>>x[],string dir1)
{
   int a,b,c,i=0;
   //string dir=getenv("HOME");
   string dir=dir1+"/Documents/RSA/data.txt";
   fstream f(dir);
   //fstream f("C:\\Users\\user\\Downloads\\data.txt");
   while(f>>a>>b>>c)
   {
      //a--,b--;
      //undirected
      x[a].push_back({b,c});
      x[b].push_back({a,c});
   }
   f.close();
}
