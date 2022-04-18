#include"bits/stdc++.h"
#include"../insert/insertion.cpp"
//#include"sets_ld/set_eq_paths.cpp"
#include"../gen_p/gen.cpp"
#include"../sets_ld/sets_ini.cpp"
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
         wt.resize(l,INT_MAX);
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
      void ins(vector<int>a,vector<int>a12,int l,int i,string dir1,vector<vector<int>>tmp_s,vector<vector<int>>&score)
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
            if(wt[j]!=INT_MAX)continue;//cout<<"s\n";
            if(a[j]==INT_MAX)continue;
            wt[j]=a[j];//storing weight in DS
            while(a12[x1]!=i)
            {
               link.push(x1);
               //cout<<x1<<" "<<i<<" "<<a12[x1]<<" "<<j<<"\n";
               score[x1][a12[x1]]=tmp_s[x1][a12[x1]];
               score[a12[x1]][x1]=tmp_s[a12[x1]][x1];
               x1=a12[x1];
            }
            link.push(x1);//second node
            link.push(i);//source node
            score[x1][i]=tmp_s[i][x1];
            score[i][x1]=tmp_s[x1][i];
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
      void rem_path(int i,int l)
      {
          for(int i=0;i<l;i++)
         
          pth[i].clear();
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
      void ins_spec_bk(int sp,int ind,int arr,int arr1)/////////for inserting spectrum in array
      {
        /*
            sp=no. of spectrum
            ind=starting index
            arr=selects spectrum array
            arr1=selects spectrum array
            arr & arr1 are taken as 1-2 & 2-1 will have same spectrum array
        */
        int i;
        //printf("ind %d sp %d\n",ind,sp);
        for(i=ind;i<=sp;i++)sp_alloc[arr][i]=1;//filling array with spectrum
        for(i=ind;i<=sp;i++)sp_alloc[arr1][i]=1;//filling array with spectrum
        sp_alloc[arr][i]=-1;//filling last position with guard bit
        sp_alloc[arr1][i]=-1;//filling last position with guard bit
        mx_sp_ptr[arr]=ind+sp;//updating max index 
        mx_sp_ptr[arr1]=ind+sp;//updating max index 
        for(i=0;i<3000;i++)
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
    {//cout<<"S\n";
        a1=pq.top().second;//vertex
        pq.pop();
        if(v[a1]==true)continue;
        v[a1]=true;//setting vertex as visited
        for(auto i:x[a1])
        {
            c=i.first;//vertex
            d=i.second;//weight
            
            //else v_p[a1][c]++;
            //cout<<"s";
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
                cout<<"checking\n";
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
                    cout<<tmp_p<<" "<<link.top()<<" threshold "<<v_p[tmp_p][link.top()]<<" ";
                    if(v_p[tmp_p][link.top()]>threshold||v_p[link.top()][tmp_p]>threshold)tmp_v=1;
                }cout<<"\n";
                if(tmp_v)continue;
               cout<<"passed\n";
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
                    v_p[link.top()][tmp_p]+=1;
                    cout<<tmp_p<<" "<<link.top()<<" threshold "<<v_p[tmp_p][link.top()]<<" ";
                }cout<<"\n";
	        }//cout<<c<<" "<<a1<<"\n";
        }//cout<<"S";
    }
    return v_p;
}
int checker(int a1,int c,vector<int>v)
{
    for(int i=0;i<v.size()-1;i++){//cout<<v[i]<<"\n";
        if(v[i]==a1&&v[i+1]==c||v[i]==c&&v[i+1]==a1){//cout<<a1<<" "<<c<<"\n";
        return 1;}
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
        {//cout<<"s\n";
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
                    if(score[tmp_p][link.top()]>threshold||score[link.top()][tmp_p]>threshold)tmp_v=1;
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
                    score[link.top()][tmp_p]+=1;
                }
            }}
        }
        return score;
}
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
            }if(!f1)f1=ind+f;
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
            for(k=0;k<tmp1[j].size()-1;k++)n[tmp1[j][k]].ins_spec_bk(b_ind[1],b_ind[0],tmp1[j][k+1],tmp1[j][k]);
         }
      }
   }
}
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
    queue<int>q;
    q.push(0);
    //for primary path
    vector<int>visited(l,0);
    vector<vector<int>>ds_path;
    while(!q.empty())
    { //cout<<"s\n";
    unordered_map<int,int>array_v;
        if((!q.empty())&&visited[q.front()])
        {
            q.pop();
            continue;
        }
        i=0;t=0;
        //cout<<q.front()<<"\n";
        while(i<l)
        {
            if(visited[i])
            {
                i++;
                continue;
            }
            
            vector<int>path_link(2000,0);
            vector<int>weights(l,INT_MAX);
            if(!v[i])n[i]=node(l,i);
            v[i]=1;
            vector<vector<int>>tmp;
            //vector<vector<int>>tmp_score(l,vector<int>(l,0));
            //tmp_score=score;
            //cout<<"s\n";
            tmp=dijk(x,l,weights,i,path_link,score,threshold);
            //cout<<"s\n";
            ds_path=tmp;
            /*vector<vector<int>>tmp1; 
                 tmp1=ds_path;*/
                 //score=ds_path;
                 n[i].ins(weights,path_link,l,i,dir1,ds_path,score);
            //cout<<i<<"\n";
            for(int j=0;j<l;j++)
            {//cout<<"s\n";
                if(i==j)continue;
                if(weights[j]==INT_MAX)
                {
                    q.push(i);
                    array_v[i]=1;
                    cout<<i<<" path "<<j<<" ";
                     t=1;break;
                }
           
            }
            cout<<"threshold & t "<<threshold<<" "<<t<<"\n";
            for(int i1=0;i1<score.size();i1++)
            {
	          for(int j=0;j<score[i1].size();j++)cout<<score[i1][j]<<" ";
	            cout<<"\n";
            }cout<<"------------\n";
       
        //if(threshold>5)exit(0);
         i++;}if(t==1)threshold++;
        for(int i=0;i<l;i++)if(array_v[i]!=1)visited[i]=1;
        }
 cout<<"Backup\n";

        vector<vector<int>>visited_bk(l,vector<int>(l,0));
        q.push(0);
         while(!q.empty()){int t1=0;
            q.pop();
            i=0;
                while(i<l){
                 j=0;
                  t=0;
                 //cout<<i<<"\n";
                while(j<l)//////////backup first checks
                {
                   
                    vector<int>path_link(2000,0);
                    vector<int>path;
                    vector<vector<int>>tmp1;
                    //cout<<j<<"\n";
                    vector<int>weights(l,INT_MAX);
                    vector<int>v23;
                    if(i==j||visited_bk[i][j])
                    {
                        j++;
                        continue;
                    }
                            v23=n[i].rt_pth(j);
                            
                         /* for(auto it:v23)
                          {
                              cout<<it<<" ";
                            
                          }cout<<"\n";*/
                          // cout<<i<<" "<<tmp1[i][4]<<" "<<threshold<<"\n";
                          
                    tmp1=bckup(x,l,weights,i,path_link,score,threshold,v23);
                            //cout<<i<<" "<<tmp1[i][4]<<" "<<threshold<<"\n";
                     //cout<<i<<" "<<j<<" "<<threshold<<"\n";
                        if(weights[j]==INT_MAX)
                        {//cout<<i<<" "<<j<<"-----------------\n";
                        
                        t=1;
                            
                            
                        }else {visited_bk[i][j]=1;
                         int x1;
                            stack<int>link;
                            x1=j;
                            if(x1==i)continue;
                            //wt[j]=a[j];//storing weight in DS
                            //cout<<j<<"j\n ";
                            while(path_link[x1]!=i)
                            {//cout<<"f\n";
                                link.push(x1);
                                score[x1][path_link[x1]]=tmp1[x1][path_link[x1]];
                                score[path_link[x1]][x1]=tmp1[path_link[x1]][x1];
                                x1=path_link[x1];
                            }
                            link.push(x1);//second node
                            link.push(i);//source node
                            score[x1][i]=tmp1[x1][i];
                           score[i][x1]=tmp1[i][x1];
                            while(!link.empty()){//cout<<"s\n";
                                path.push_back(link.top());
                                link.pop();}
                            //score=tmp1;
                            n[i].ins_b_path(path,j);}
                   j++; 
                    //cout<<j<<"\n";
                }if(t==1){q.push(i);t1=1;}i++;
              /*  if(t)
                {
                    t=0;
                    //cout<<i<<"\n";
                    //cout<<i<<" "<<score[i][4]<<" "<<threshold<<"\n";
                    
                    n[i].rem_path(i,l);
                    i++;
                    //threshold++;
                    continue;
                }*/
                ///////if backup path is good
                
                //cout<<"c\n";
                
                
    
                //cout<<i<<"\n";
            
            
      /*  for(int i=0;i<score.size();i++)
    {
	    for(int j=0;j<score[i].size();j++)
	    cout<<score[i][j]<<" ";
	    cout<<"\n";
	    
    }cout<<"threshold "<<threshold;*/
       

         }if(t1==1)threshold++;
         }
    for(int i=0;i<score.size();i++)
    {
	    for(int j=0;j<score[i].size();j++)
	    cout<<score[i][j]<<" ";
	    cout<<"\n";
	    
    }cout<<"threshold "<<threshold;
        ////////for link disjoint backup path
        
      sets st(l);
    
    int a,b,c,d,f;
    int mf[]={8000,4000,2000,1000,500,250};//modulation frequency based on different ranges
    //string dir1=getenv("HOME");
    //gen_path(l,dir1);
    string dir;
    dir=dir1+"/Documents/RSA/data2.txt";
    //cout<<dir<<"\n";
    fstream f3(dir);
    
     while(f3>>a>>b>>c)//taking input
      {d=n[a].rt_wt(b);
        
        vector<int>v2;
        v2=n[a].rt_pth(b);
                    //for(int k=0;k<v2.size();k++)
                        //cout<<v2[k]<<"\n";
        vector<int>v1;
        v1=n[a].rt_b_pth(b);
                    //for(int k=0;k<v1.size();k++)
                        //cout<<v1[k]<<" ";
                        //cout<<"\n";
        for(i=5;i>=0;i--)
         {
            if(mf[i]>=d)
            {
               d=i+1;//Sepectrum efficiency
               break;
            }
         }
         f=ceil(c/(12.5*d));
        st.ins_set(v2,v1);
            st.ins_requests(a,b,f);
            //cout<<"\n";
        
        }
        
  /*  for(int i=0;i<l;i++)
    
        n[i].prnt_b_path(l,dir1,i);*/
        
    
    st.print_pset(dir1);
    st.print_bset(dir1);
    checkNins(st,n,l);
    cout<<"max spectrum array & max subcarrier index\n"<<maxx(l,n)<<"\n";
}
