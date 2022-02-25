#include"bits/stdc++.h"
using namespace std;
//////////////Finding Shortest Path
void dijk(vector<pair<int,int>>x[],int l,vector<int>&a,int s,int a12[])
{
    //min heap queue to store least weight wise
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    vector<bool>v(l,false);
    a[s]=0;
    pq.push({0,s});
    int a1,c,d;
    while(!pq.empty())
    {
        a1=pq.top().second;//vertex
        pq.pop();
        if(v[a1]==true)continue;
        v[a1]=true;//setting vertex as visited
        for(auto i:x[a1])
        {
            c=i.first;//vertex
            d=i.second;//weight
            if(a[a1]+d<a[c])a[c]=a[a1]+d,pq.push({a[c],c}),a12[c]=a1;//storing least weighted vertex and path
        }
    }
}