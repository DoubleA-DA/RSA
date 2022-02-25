#include"bits/stdc++.h"
using namespace std;
///////////////Creating DS
/*
    insertion & storing of primary set for link disjoint paths
    insertion & storing of backup set for common link paths
*/
class sets
{
    unordered_map<int,vector<vector<int>>>prim_set;//primary set for link disjoint paths
    vector<vector<int>>reqs;//storage of requests
    vector<vector<int>>p_path;//for checking if backup path has common links with primary path
    vector<vector<int>>b_path;//sharing of backup path
    unordered_map<int,vector<vector<int>>>bck_set;//backup set for common link paths
    public:
        sets(int l)
        {
           reqs.resize(l);
           for(int i=0;i<l;i++)reqs[i]=vector<int>(l,0);
           p_path.resize(l);
           for(int i=0;i<l;i++)p_path[i]=vector<int>(l,0);
           b_path.resize(l);
           for(int i=0;i<l;i++)b_path[i]=vector<int>(l,0);
        }
        void ins_set(vector<int>path,vector<int>b_path)
        {
            int s=prim_set.size(),i,sw=1,it=0,k=0,cnt=0,j;
            vector<vector<int>>v,v1,v2;
            for(i=0;i<s;i++)
            {
                //if(prim_set[i])
                sw=1;
                v1=prim_set[i];
                v2=bck_set[i];
                for(it=0;it<v1.size();it++)
                {
                    cnt=0;
                    for(j=0;j<path.size();j++)
                    {
                        if(cnt==2)break;
                        for(k=0;k<v1[it].size();k++)
                        {
                            if(path[j]==v1[it][k])
                            {
                                cnt++;
                                if(cnt==2)
                                {
                                    if(k!=v1[it].size()-1&&v1[it][k+1]==path[j-1])true;
                                    else if(k!=0&&v1[it][k-1]==path[j-1])true;
                                    else cnt--;
                                }
                                break;
                            }
                        }              
                    }
                    if(cnt==2)break;
                }
                if(cnt!=2)
                {
                    sw=0;
                    v1.push_back(path);
                    v2.push_back(b_path);
                    prim_set[i]=v1;
                    bck_set[i]=v2;
                    break;
                }
                if(!sw)break;
            }
            //////////if link is not disjoint
            if(sw)
            {
                v.push_back(path);
                int pos=prim_set.size();
                prim_set[pos]=v;//set 1
                v.clear();
                v.push_back(b_path);//set 2
                bck_set[pos]=v;
            }
        }
        void print_pset(string dir1)
        {
            string dir=dir1+"/Documents/RSA/prim_set.txt";
            fstream f1(dir,ios_base::app);
            for(int i=0;i<prim_set.size();i++)
            {
                vector<vector<int>>v=prim_set[i];
                cout<<"Set "<<i<<"\n";
                f1<<"Set "<<i<<"\n";
                for(auto j:v)
                {
                for(auto k:j)
                {
                   f1<<k<<" ";
                   cout<<k<<" ";
                }
                cout<<"\n";
                f1<<"\n";
                }
            }
            f1.close();
        }
        void print_bset(string dir1)
        {
            string dir=dir1+"/Documents/RSA/bck_set.txt";
            fstream f1(dir,ios_base::app);
            for(int i=0;i<bck_set.size();i++)
            {
                vector<vector<int>>v=bck_set[i];
                cout<<"bck Set "<<i<<"\n";
                f1<<"Set "<<i<<"\n";
                for(auto j:v)
                {
                for(auto k:j)
                {
                   f1<<k<<" ";
                   cout<<k<<" ";
                }
                cout<<"\n";
                f1<<"\n";
                }
            }
        }
        vector<vector<int>> rt_prim_set(int i)
        {
           return prim_set[i];
        }
        vector<vector<int>> rt_bck_set(int i)
        {
           return bck_set[i];
        }
        void ins_requests(int a,int b,int c)
        {
           reqs[a][b]=c;
        }
        void ins_pth(int a,int b)//Sets path as visited
        {
           p_path[a][b]=1;
           p_path[b][a]=1;
        }
        bool chk_bckup(int a,int b)
        {
           if(p_path[a][b]||p_path[b][a])return false;
           return true;
        }
        int rt_reqs(int a,int b)
        {
           return reqs[a][b];
        }
        int rt_set_siz()
        {
           return prim_set.size();
        }
};