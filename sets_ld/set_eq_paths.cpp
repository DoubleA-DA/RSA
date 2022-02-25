#include"bits/stdc++.h"
using namespace std;
class set{
    unordered_map<int,vector<vector<int>>>p_path;
    unordered_map<int,vector<vector<int>>>b_path;
    vector<vector<int>>weight;
    public:
    void ins_p_path(int start,vector<int>path)
    {
        p_path[start].push_back(path);
    }
    int ins_b_path(int start,vector<int>path)
    {
        int cnt=0;
        for(int i=0;i<path.size()-1;i++)
        {
            for(int j=0;j<p_path[start].size();j++)
            {
                for(int k=0;k<p_path[start][j].size();k++)
                {
                    if(path[i]==p_path[start][j][k])cnt++;
                    if(cnt==2)
                    {
                        if(k!=p_path[start][j].size()-1&&p_path[start][j][k+1]==path[i-1])return -1;
                        else if(k!=0&&p_path[start][j][k-1]==path[i-1])return -1;
                        else cnt--;
                    }
                }
            }
        }
        b_path[start].push_back(path);
        return 1;
    }
    int ins_weight(int wt)
    {
        
        return 1;
    }
};