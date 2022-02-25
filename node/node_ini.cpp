#include"bits/stdc++.h"
using namespace std;
/////////////////////Creating DS 
/*
    inserting & storing primary path & backup
    allocation of spectrum in spectrum array
*/
class node
{
   vector<vector<int>>pth;//path
   vector<vector<int>>b_pth;//backup path
   vector<vector<int>>b2_pth;//2nd backup path
   vector<int>wt;//weight
   vector<vector<int>>sp_alloc;//spectrum array
   vector<int>sp_ptr;//spectrum pointer
   vector<int>mx_sp_ptr;//max spectrum pointer
   public:
      node(){};//for declaring node size without the constructor at frist
      node(int l,int i)//constructor
      {
         pth.resize(l);
         wt.resize(l);
         b_pth.resize(l);
         sp_alloc.resize(l);
         /*for(int j=0;j<l;j++)//for the spectrum array
         {
            if(j==i||j<i)continue;
            sp_alloc[j]=vector<int>(1000,0);
         }*/
         sp_ptr.resize(l);
         mx_sp_ptr.resize(l);
      }
      /*
         storing path,weight in DS
         writing primary path in file data3
      */
      void ins(vector<int>a,int a12[],int l,int i,string dir1)
      {
         //string dir=getenv("HOME");
         string dir=dir1+"/Documents/RSA/data3.txt";
         cout<<"s";
         fstream f2(dir,ios_base::app);
         //fstream f2("C:\\Users\\user\\Downloads\\data3.txt",ios_base::app);//link 
         int j,x1;
         //////////////Calculating and inserting path in ds
         for(j=0;j<l;j++)
         {
            stack<int>link;
            x1=j;
            if(x1==i)continue;
            wt[j]=a[j];//storing weight in DS
            while(a12[x1]!=i)
            {
               link.push(x1);
               x1=a12[x1];
            }
            link.push(x1);//second node
            link.push(i);//source node
            while(!link.empty())
            {
               f2<<link.top()<<" ";//writing path
               sp_alloc[link.top()]=vector<int>(1000,0);//initializing spectrum array
               pth[j].push_back(link.top());//storing path in ds
               link.pop();
            }
            f2<<"\n";
         } 
         f2.close();
         //////////////////////////////////////
      }
      void ins_b_path(vector<int>pth,int pos)
      {
        b_pth[pos]=pth;
      }
      vector<int> rt_pth(int a)
      {
        return pth[a];
      }
      vector<int> rt_b_pth(int a)
      {
        return b_pth[a];
      }
      int rt_wt(int a)
      {
        return wt[a];
      }
      int rt_sp(int i)
      {
        return sp_ptr[i];
      }
      int rt_max_sp(int i)
      {
        return mx_sp_ptr[i];
      }
      vector<int> rt_sp_arr(int i)
      {
        return sp_alloc[i];
      }
      void ins_spec(int sp,int ind,int arr,int arr1)/////////for inserting spectrum in array
      {
        /*
            sp=no. of spectrum
            ind=starting index
            arr=selects spectrum array
            arr1=selects spectrum array
            arr & arr1 are taken as 1-2 & 2-1 will have same spectrum array
        */
        int i;
        for(i=ind;i<=ind+sp;i++)sp_alloc[arr][i]=1;//filling array with spectrum
        for(i=ind;i<=ind+sp;i++)sp_alloc[arr1][i]=1;//filling array with spectrum
        sp_alloc[arr][i]=-1;//filling last position with guard bit
        sp_alloc[arr1][i]=-1;//filling last position with guard bit
        mx_sp_ptr[arr]=ind+sp;//updating max index 
        mx_sp_ptr[arr1]=ind+sp;//updating max index 
        for(i=0;i<1000;i++)
        {
           if(!sp_alloc[arr][i])
           {
              sp_ptr[arr]=i;//updating index
              sp_ptr[arr1]=i;//updating index
              break;
           }
        }
      }
      void prnt_spec(int arr)
      {
         for(int i=0;i<1000;i++)cout<<sp_alloc[arr][i];
         cout<<"\n";
      }
};