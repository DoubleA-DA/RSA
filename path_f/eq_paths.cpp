#include"bits/stdc++.h"
#include"../insert/insertion.cpp"
//#include"sets_ld/set_eq_paths.cpp"
//#include"node/node_ini.cpp"
using namespace std;
string dir1=getenv("HOME");
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
      void ins(vector<int>a,vector<int>a12,int l,int i,string dir1)
      {
         //string dir=getenv("HOME");
         string dir=dir1+"/Documents/RSA/data3.txt";
         //cout<<"s";
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
               //cout<<x1<<" "<<i<<" "<<a12[x1]<<" "<<j<<"\n";
               x1=a12[x1];
            }
            link.push(x1);//second node
            link.push(i);//source node
            while(!link.empty())
            {
               f2<<link.top()<<" ";//writing path
               //cout<<link.top()<<"\n";
	       //int var=link.top();
               sp_alloc[link.top()]=vector<int>(1000,0);//initializing spectrum array
               pth[j].push_back(link.top());//storing path in ds
               link.pop();
	       //v_p[var][link.top()]+=1;
            }
            f2<<"\n";
         } 
         f2.close();
	 //return v_p;
         //////////////////////////////////////
      }
      void ins_b_path(vector<int>pth,int pos)
      {
        b_pth[pos]=pth;
      }
      void prnt_b_path(int l,string dir,int j)
      {
          dir=dir+"/Documents/RSA/data4.txt";
          fstream f5(dir,ios_base::app);
          for(int i=0;i<l;i++)
          {
              
            if(i==j)continue;
            vector<int>v;
            v=b_pth[i];
            for(int k=0;k<v.size();k++)
                f5<<v[k]<<" ";
            f5<<"\n";
          }
          f5.close();
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

//////////////Finding Shortest Path
vector<vector<int>> dijk(vector<pair<int,int>>x[],int l,vector<int>&a,int s,vector<int>& a12,vector<vector<int>>v_p,int threshold)
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
            
            //else v_p[a1][c]++;
            
            if(a[a1]+d<a[c])
	        {
                int tmp_v=0;
                vector<int>a12_1;
                a12_1=a12;
                a12_1[c]=a1;
                stack<int>link;
                int x1=c;
                //if(x1==i)continue;
                //wt[j]=a[j];//storing weight in DS
                while(a12_1[x1]!=s)
                {
                link.push(x1);
                x1=a12_1[x1];
                //cout<<a12_1[x1]<<" "<<s<<"\n";
                }
                link.push(x1);//second node
                link.push(s);//source node
                while(!link.empty())
                {
                    int tmp_p=link.top();
                    link.pop();
                    if(link.empty())break;
                    if(v_p[tmp_p][link.top()]>threshold)tmp_v=1;
                }
                if(tmp_v)continue;

		        a[c]=a[a1]+d,pq.push({a[c],c}),a12[c]=a1;//storing least weighted vertex and path
		        //cout<<c<<" "<<a1<<"\n";
		        
                //stack<int>link;
                x1=c;
                //if(x1==i)continue;
                //wt[j]=a[j];//storing weight in DS
                a12_1=a12;
                while(a12_1[x1]!=s)
                {
                link.push(x1);
                x1=a12_1[x1];
                }
                link.push(x1);//second node
                link.push(s);//source node
                while(!link.empty())
                {
                    int tmp_p=link.top();
                    link.pop();
                    if(link.empty())break;
                    v_p[tmp_p][link.top()]+=1;
                }
	        }
        }
    }
    return v_p;
}
int checker(int a1,int c,vector<int>v)
{
    for(int i=0;i<v.size()-1;i++){//cout<<v[i]<<"\n";
        if(v[i]==a1&&v[i+1]==c||v[i]==c&&v[i+1]==a1)return 1;
    }
    return 0;
}
vector<vector<int>> bckup(vector<pair<int,int>>x[],int l,vector<int>&weights,int i,vector<int>& path_link,vector<vector<int>>score,int threshold,vector<int>v23)
{
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
        vector<bool>v_f(l,false);
        weights[i]=0;
        pq.push({0,i});
        int a1,c,d;//cout<<pq.size()<<"\n";
        //cout<<"x\n";
        while(!pq.empty())
        {
            a1=pq.top().second;//vertex
            pq.pop();
            if(v_f[a1]==true)continue;
            v_f[a1]=true;//setting vertex as visited
            //cout<<"x\n";
            for(auto i1:x[a1])
            {
                c=i1.first;//vertex
                d=i1.second;//weight
                //cout<<v23[0]<<"\n";
                if(checker(a1,c,v23))continue;
                //score[a1][c]++;
                if(weights[a1]+d<weights[c])
                {
                   
	        
                int tmp_v=0;
                vector<int>path_link_1;
                path_link_1=path_link;
                path_link_1[c]=a1;
                stack<int>link;
                int x1=c;
                //if(x1==i)continue;
                //wt[j]=a[j];//storing weight in DS
                while(path_link_1[x1]!=i)
                {
                link.push(x1);
                x1=path_link_1[x1];
                }
                link.push(x1);//second node
                link.push(i);//source node
                while(!link.empty())
                {
                    int tmp_p=link.top();
                    link.pop();
                    if(link.empty())break;
                    if(score[tmp_p][link.top()]>threshold)tmp_v=1;
                }//path_link[c]=0;
                if(tmp_v)continue;
                
                weights[c]=weights[a1]+d,pq.push({weights[c],c}),path_link[c]=a1;//storing least weighted vertex and path
                
                
                 x1=c;
                //if(x1==i)continue;
                //wt[j]=a[j];//storing weight in DS
                while(path_link[x1]!=i)
                {
                    //cout<<x1<<" "<<i<<"\n";
                link.push(x1);
                x1=path_link[x1];
                }
                link.push(x1);//second node
                link.push(i);//source node
                while(!link.empty())
                {
                    int tmp_p=link.top();
                    link.pop();
                    if(link.empty())break;
                    score[tmp_p][link.top()]+=1;
                }
            }}
        }
        return score;
}
int main()
{
   //ios_base::sync_with_stdio(false); 
   //cin.tie(NULL);    
   int l,x1,j;
   
      cin>>l;
      vector<pair<int,int>>x[l];
      add(x,dir1);
    node* n=new node[l];
    int threshold=0,destination,t=0,i=0;
    vector<vector<int>>score(l,vector<int>(l,0));
    //string dir=dir1+"/Documents/RSA/data_test.txt";
    
    //fstream f5(dir,ios_base::app);
    vector<bool>v(l,0);
    //for primary path
    while(i<l)
    {
        t=0;
        vector<int>path_link(2000,0);
        vector<int>weights(l,INT_MAX);
        if(!v[i])n[i]=node(l,i);
        v[i]=1;
        vector<vector<int>>tmp;
        
        tmp=dijk(x,l,weights,i,path_link,score,threshold);
        //cout<<i<<"\n";
        for(int j=0;j<l;j++)
        {
            if(i==j)continue;
            if(weights[j]==INT_MAX)
            {
                t=1;
                break;
            }
            //cout<<weights[j]<<" ";
            //cout<<i<<" ";
            //if(!t)score[i][j]++;
        }//cout<<i<<" ";
        if(!t)
        {//cout<<path_link[5]<<"\n";
            n[i].ins(weights,path_link,l,i,dir1);
            
            score=tmp;
                /*for(int j=0;j<l;j++){
                    if(j==i)continue;
                    vector<int>v22;
                    v22=n[i].rt_pth(j);
                    //for(int k=0;k<v22.size()-1;k++){cout<<v22[k]<<" ";
			    //score[v22[k]][v22[k+1]]++;
		    //}cout<<"\n";
                      // cout<<v22[k]<<" ";
                }*/
            i++;
        }
        else threshold++;
    }
    ////////for link disjoint backup path
    cout<<threshold<<"end\n";
    for(int i=0;i<score.size();i++){
	    for(int j=0;j<score[i].size();j++)cout<<score[i][j]<<" ";
    cout<<"\n";}
	    i=0;
    while(i<l)
    {
        //t=0;
        


    //cout<<i<<"\n";
        
        j=0;
        while(j<l)
        {t=0;
        vector<int>path_link(2000,0);
        vector<int>path;
        //cout<<j<<"\n";
        vector<int>weights(l,INT_MAX);
        vector<int>v23;if(i==j){j++;continue;}
                v23=n[i].rt_pth(j);
             vector<vector<int>>tmp;   
        tmp=bckup(x,l,weights,i,path_link,score,threshold,v23);

        //for(int i1=0;i1<v23.size();i1++)cout<<v23[i1]<<"\n";

        //cout<<i<<"\n";






        
        
            if(weights[j]==INT_MAX)
            {
                t=1;
                
            }
        
        if(!t)
        {
            //cout<<j<<"j\n ";
                //if(i==j)continue;
                int x1;
                stack<int>link;
                x1=j;
                if(x1==i)continue;
                //wt[j]=a[j];//storing weight in DS
                //cout<<j<<"j\n ";
                while(path_link[x1]!=i)
                {
                    link.push(x1);
                    x1=path_link[x1];
                    //cout<<"S\n";
                }
                link.push(x1);//second node
                link.push(i);//source node
                while(!link.empty()){
                    path.push_back(link.top());
                     link.pop();}
                score=tmp;
                n[i].ins_b_path(path,j);
                //cout<<"o\n";
                
                j++;
        }
        else threshold++;
        }i++;
    }cout<<threshold<<"\n";
    for(int i=0;i<l;i++)
    {
        for(int j=0;j<l;j++)
        {
            if(i==j)continue;
                vector<int>v2;
                v2=n[i].rt_pth(j);
                //for(int k=0;k<v2.size();k++)
                    //cout<<v2[k]<<"\n";
                vector<int>v1;
                v1=n[i].rt_b_pth(j);
                //for(int k=0;k<v1.size();k++)
                    //cout<<v1[k]<<" ";
                    //cout<<"\n";
        }//cout<<"\n";
    
    }
    for(int i=0;i<l;i++)
    
        n[i].prnt_b_path(l,dir1,i);
    
    for(int i=0;i<score.size();i++)
    {
	    for(int j=0;j<score[i].size();j++)
	    cout<<score[i][j]<<" ";
	    cout<<"\n";
	    
    }
}
