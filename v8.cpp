#include"bits/stdc++.h"
#include"insert/insertion.cpp"
#include"node/node_ini.cpp"
#include"sets_ld/sets_ini.cpp"
#include"path_f/dijk.cpp"
//#include"path_f/eq_paths.cpp"
#include"gen_p/gen.cpp"
#include"path_f/bck_ins.cpp"
using namespace std;
string dir1=getenv("HOME");
/*void dijk(vector<pair<int,int>>x[],int l,vector<int>&a,int s,int a12[],vector<int>&v_p,int threshold)
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
            if(v_p[c]>threshold)continue;
            if(a[a1]+d<a[c])a[c]=a[a1]+d,pq.push({a[c],c}),a12[c]=a1;//storing least weighted vertex and path
        }
    }
}
void driver(vector<pair<int,int>>x[],int l,string dir1,node n[])
{
    int threshold=0,destination,t=0,i=0;
    vector<int>score(l,0);
    string dir=dir1+"/Documents/RSA/data_test.txt";
    fstream f5(dir,ios_base::app);
    vector<bool>v(l,0);
    while(i<l)
    {
        t=0;
        int path_link[2000];
        vector<int>weights(l,INT_MAX);
        if(!v[i])n[i]=node(l,i);
        v[i]=1;
        dijk(x,l,weights,i,path_link,score,threshold);
        
        
        for(int j=0;j<l;j++)
        {
            if(weights[j]==INT_MAX)
            {
                t=1;
                continue;
            }
            f5<<i<<" "<<j<<" "<<weights[j]<<"\n";
            cout<<weights[j]<<" ";
            if(!t)score[j]++;
        }
        //if(!t)n[i].ins(weights,path_link,l,i,dir);
        if(!t)score[i]++,i++;
        else threshold++;
    }
}*/
/////////////////////////searches second backup path
int backup_path(vector<pair<int,int>>x[],int a14[],vector<int>&v,vector<int>&v_1,int l,vector<int>&a,int s,int b)
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
            if(v[c]&&v[a1]||v_1[c]&&v_1[a1])continue;//checking if path visited
            if(a[a1]+d<a[c])a[c]=a[a1]+d,pq.push({a[c],c}),a14[c]=a1;//storing least weighted vertex and path
            //cout<<a14[c];
        }
    }
    if(a[b]==INT_MAX)return -1;//if no path found
    return 0;
}
/////////////////getting max index and max indexed array
int maxx(int l,node* n)
{
   int i,j,mx=0,i1=0,j1=0;
   for(i=0;i<l;i++)
   {
      for(j=0;j<l;j++)
      {
         if(i==j)continue;
         if(mx<n[i].rt_max_sp(j))mx=n[i].rt_max_sp(j),i1=i,j1=j;
      }
   }
   n[i1].prnt_spec(j1);
   return mx;
}

////////////////////////checking for contiguous and continuous allocation index
int chk_ind(vector<int>v1,int f,int l,node* n)
{
    int i,mx1=0,a1,b1,j,d=0;
    /////////////////checking for highest index of subcarriers in the path
    for(i=1;i<v1.size();i++)
         {
            if(n[v1[d]].rt_sp(v1[i])>=mx1)a1=d,b1=i,mx1=n[v1[d]].rt_sp(v1[i]);
            d=i;
            /*
               a1 = start
               b1 = end
               mx1 = highest index
            */
         }
         ///////////////////////////////////////////////////////////////
         int count_spec=0,ind=mx1,sw;
         /*
            count_spec = counts till f
            ind = index for free contiguous and continous space
            sw = flag
         */
         while(1)
         {
            vector<int>v3;
            v3=n[a1].rt_sp_arr(b1);/////////storing spectrum array
            if(ind!=mx1)/////first time it skips, only checks if other indexes are full
            {
               for(i=ind;i<v3.size();i++)
               {
                  if(!v3[i])count_spec++;
                  else count_spec=0;
                  if(count_spec==(f+1))
                  {
                     ind=i-count_spec;//extracting the position of the index
                     break;
                  }
               }
            }
            /////////////checking for all the indexes in path to make it continous
            for(i=0;i<v1.size()-1;i++)
            {
               sw=0;
               v3=n[v1[i]].rt_sp_arr(v1[i+1]);
               for(j=ind;j<ind+f+1;j++)
               {
                  if(v3[j])
                  {
                     sw=1;
                     break;
                  }
               }
               if(sw)break;
            }
            if(!sw)break;//if sw==0 got the node
            ind+=f;//updating index with required spectrum and checking it again if sw==1
            if(ind>=999)////////checking for overflow of slots in the spectrum array
            {
               //cout<<"overflow "<<maxx(l,n);
               //exit(0);
               return -1;
            }
         }
         return ind;
}
///////////checking for allocation of spectrum in backup path
vector<int>chk_bck_ind(vector<int>v1,int f,int l,node* n)
{
    int i,mx1=0,a1,b1,j,d=0;
    /////////////////checking for highest index of subcarriers in the path
    for(i=1;i<v1.size();i++)
         {
            if(n[v1[d]].rt_sp(v1[i])>=mx1)a1=d,b1=i,mx1=n[v1[d]].rt_sp(v1[i]);
            d=i;
            /*
               a1 = start
               b1 = end
               mx1 = highest index
            */
         }
         ///////////////////////////////////////////////////////////////
         int count_spec=0,ind=mx1,sw,cnt_1=0,f1=0;
         /*
            count_spec = counts till f
            ind = index for free contiguous and continous space
            sw = flag
            f1 = remaning of the shared spectrum
         */
         while(1)
         {
            vector<int>v3;
            v3=n[a1].rt_sp_arr(b1);/////////storing spectrum array
            if(ind!=mx1)/////first time it skips, only checks if other indexes are full
            {
               for(i=ind;i<v3.size();i++)
               {
                  if(v3[i]!=-1)count_spec++;
                  else count_spec=0,cnt_1=0;
                  if(v3[i]==1)cnt_1++;
                  if(!v3[i])cnt_1=0;
                  if(count_spec==f)
                  {
                     f1=count_spec-cnt_1;
                     ind=i-f1;//extracting the position of the index
                     break;
                  }
               }
            }
            /////////////checking for all the indexes in path to make it continous
            for(i=0;i<v1.size()-1;i++)
            {
               sw=0;
               v3=n[v1[i]].rt_sp_arr(v1[i+1]);
               for(j=ind;j<ind+f;j++)
               {
                  if(v3[j])
                  {
                     sw=1;
                     break;
                  }
               }
               if(sw)break;
            }
            if(!sw)break;//if sw==0 got the node
            ind+=f;//updating index with required spectrum and checking it again if sw==1
            if(ind>=999)////////checking for overflow of slots in the spectrum array
            {
               //cout<<"overflow "<<maxx(l,n);
               //exit(0);
               return {-1,0};
            }
         }
         return {ind,f1};
}

//////////////Inserts and checks spectrum for SPP
void checkNins(sets st,node* n,int l)
{
   int i,j,k,sp,cnt=0,sw,p_ind;
   vector<int>b_ind(2);
   for(i=0;i<st.rt_set_siz();i++)
   {
      vector<vector<int>>tmp=st.rt_prim_set(i);
      vector<vector<int>>tmp1=st.rt_bck_set(i);
      for(j=0;j<tmp.size();j++)
      {
         cnt=0,sw=0;
         for(k=0;k<tmp1[j].size()-1;k++)//////for checking if backup path collides with primary path
         {
            if(st.chk_bckup(tmp1[j][k],tmp1[j][k+1])==false)//comparing backup path w/ priamry path
            {
               cnt=1;
               break;
            }
         }
         for(k=0;k<tmp[j].size()-1;k++)////taking spectrum and making path as visited
         {
            if(cnt)break;
            if(!k)sp=st.rt_reqs(tmp[j][0],tmp[j][tmp[j].size()-1]);
            st.ins_pth(tmp[j][k],tmp[j][k+1]);
         }
         if(!cnt)//inserting spectrum in primary and sharing in backup path
         {
            p_ind=chk_ind(tmp[j],sp,l,n);
            b_ind=chk_bck_ind(tmp1[j],sp,l,n);
            if(p_ind==-1||b_ind[0]==-1)continue;
            for(k=0;k<tmp[j].size()-1;k++)n[tmp[j][k]].ins_spec(sp,p_ind,tmp[j][k+1],tmp[j][k]);
            for(k=0;k<tmp1[j].size()-1;k++)n[tmp1[j][k]].ins_spec(b_ind[1],b_ind[0],tmp1[j][k+1],tmp1[j][k]);
         }
      }
   }
}
int main()
{
   //ios_base::sync_with_stdio(false); 
   //cin.tie(NULL);    
   int l,i,x1,j;
   
      cin>>l;
      vector<pair<int,int>>x[l];
      add(x,dir1);
      node* n=new node[l];//number of nodes for the map
      //string dir=getenv("HOME");
      string dir=dir1+"/Documents/RSA/data1.txt";
      //fstream f5(dir,ios_base::app);//to write sorted distance
      //fstream f5("C:\\Users\\user\\Downloads\\data1.txt",ios_base::app);//to write sorted distance
      /*for(i=0;i<l;i++)
      {
         vector<int>a(l,INT_MAX);//for storing least weights
         int a12[20000];//path link
         dijk(x,l,a,i,a12);
         n[i]=node(l,i);//intializing for the nodes
         for(j=0;j<l;j++)
         {
            if(!a[j])continue;
            f5<<i<<" "<<j<<" "<<a[j]<<"\n";//writing in file data1
         }
         n[i].ins(a,a12,l,i,dir1);
      }*/
     // driver(x,l,dir1);
      //f5.close();
      //gen_path(l,dir1);

      int a,b,a1,it=0,lp=0,b1,c,d,e=0,f;
      int mf[]={8000,4000,2000,1000,500,250};//modulation frequency based on different ranges
      //string dir1=getenv("HOME");
      dir=dir1+"/Documents/RSA/data2.txt";
      fstream f3(dir);
      string dir2=dir1+"/Documents/RSA/data4.txt";
      fstream f6(dir2,ios_base::app);//backup path
      string dir3=dir1+"/Documents/RSA/data5.txt";
      fstream f7(dir3,ios_base::app);//2nd backup path
      //fstream f3("C:\\Users\\user\\Downloads\\data2.txt");//bandwidth


      /*
         for the while loop
         taking input from the random generated path file
         allocating subcarriers slots in the dedicated paths
      */
      sets st(l);
      while(f3>>a>>b>>c)//taking input
      {
         int a13[2000],a14[2000];//backup_link
         vector<int>v(l,0),v_1(l,0);//marks which links are visited in the shortest path and backup path
         vector<int>v1,v2,v3;//primary path,backup path, 2nd backup path
         vector<int>a3(l,INT_MAX),a4(l,INT_MAX);//uses in backup_path function for comparing
         v1=n[a].rt_pth(b);
         cout<<"primary path ";
         for(auto it:v1)
         {
            cout<<it<<" ";
            e++;
            v[it]=1;
         }
         cout<<"\nweight "<<n[a].rt_wt(b)<<"\n";
         d=n[a].rt_wt(b);
         backup_path(x,a13,v,l,a3,a);
         stack<int>link;
         x1=b;
         while(a13[x1]!=a)
         {
            link.push(x1);
            x1=a13[x1];
         }
         link.push(x1);//second node
         link.push(a);//source node
         cout<<"backup path ";
         while(!link.empty())
         {
            cout<<link.top()<<" ";
            f6<<link.top()<<" ";
            v2.push_back(link.top());
            v_1[link.top()]=1;//for 2nd backup
            link.pop();
         }
         cout<<"\n2nd backup path ";
         if(backup_path(x,a14,v,v_1,l,a4,a,b)!=-1)
         {
            x1=b;
            //cout<<"X";
            while(a14[x1]!=a)
            {
               link.push(x1);
               x1=a14[x1];
            }
            link.push(x1);//second node
            link.push(a);//source node
            while(!link.empty())
            {
               cout<<link.top()<<" ";
               f7<<link.top()<<" ";
               v3.push_back(link.top());
               link.pop();
            }
         }
         else 
         {
            cout<<"-1"<<"\n";
            f7<<"-1";
         }
         cout<<"\n";
         n[a].ins_b_path(v2,b);//backup path inserting
         f6<<"\n";
         f7<<"\n";
         
         for(i=5;i>=0;i--)
         {
            if(mf[i]>=d)
            {
               d=i+1;//Sepectrum efficiency
               break;
            }
         }
         f=ceil(c/(12.5*d));
         cout<<"\nslots "<<f<<"\n";
         d=0;
         int mx1=0;
         //int ind=chk_ind(v1,f,l,n);
         ///////////////////updaitng spectrum array
         //for(i=0;i<v1.size()-1;i++)n[v1[i]].ins_spec(f,ind,v1[i+1],v1[i]);
         //cout<<"\n";
         st.ins_set(v1,v2);
         st.ins_requests(a,b,f);
      }
      //cout<<"max spectrum array & max subcarrier index\n"<<maxx(l,n)<<"\n";
      st.print_pset(dir1);
      st.print_bset(dir1);
      checkNins(st,n,l);
      cout<<"max spectrum array & max subcarrier index\n"<<maxx(l,n)<<"\n";
      
}