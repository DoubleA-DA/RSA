#include"bits/stdc++.h"
using namespace std;
///////////////////Searches backup path
void backup_path(vector<pair<int,int>>x[],int a13[],vector<int>&v,int l,vector<int>&a,int s)
{
    //min heap queue to store least weight wise
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    vector<bool>v1(l,false);
    a[s]=0;
    pq.push({0,s});
    int a1,c,d;
    while(!pq.empty())
    {
        a1=pq.top().second;//vertex
        pq.pop();
        if(v1[a1]==true)continue;
        v1[a1]=true;//setting vertex as visited
        for(auto i:x[a1])
        {
            c=i.first;//vertex
            d=i.second;//weight
            if(v[c]&&v[a1])continue;//checking if path visited/not
            if(a[a1]+d<a[c])a[c]=a[a1]+d,pq.push({a[c],c}),a13[c]=a1;//storing least weighted vertex and path
        }
    }
}