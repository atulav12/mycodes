#include<bits/stdc++.h>
using namespace std;

int t[500000],t1[500000],a[100000],n;

void build1(int node,int st,int end)
{
    if(st==end)
    {
        if(a[st]==1)
        t[node]=st;
        else
        t[node]=n;
    }
    else
    {
        int mid=(st+end)/2;
        
        build1(2*node+1,st,mid);
        build1(2*node+2,mid+1,end);
        
        t[node]=min(t[2*node+1],t[2*node+2]);
    }
}

void build2(int node,int st,int end)
{
    if(st==end)
    {
        if(a[st]==1)
        t1[node]=st;
        else
        t1[node]=-1;
    }
    else
    {
        int mid=(st+end)/2;
        
        build2(2*node+1,st,mid);
        build2(2*node+2,mid+1,end);
        
        t1[node]=max(t1[2*node+1],t1[2*node+2]);
    }
}

void up1(int node,int st,int end,int y)
{
    if(st==end)
    {
        a[y]+=1;
        t[node]=st;
    }
    else
    {
        int m=(st+end)/2;
        
        if(st<=y&&y<=m)
        up1(2*node+1,st,m,y);
        else
        up1(2*node+2,m+1,end,y);
        
        t[node]=min(t[2*node+1],t[2*node+2]);
    }
}


void up2(int node,int st,int end,int y)
{
    if(st==end)
    {
        a[y]+=1;
        t1[node]=st;
    }
    else
    {
        int m=(st+end)/2;
        
        if(st<=y&&y<=m)
        up2(2*node+1,st,m,y);
        else
        up2(2*node+2,m+1,end,y);
        
        t1[node]=max(t1[2*node+1],t1[2*node+2]);
    }
}
int query(int node,int st,int end,int l,int r,int p)
{
    if(st>r||end<l)
    {
        if(p==1)
        return INT_MAX;
        else
        return INT_MIN;
    }
    else
    {
        if(st>=l&&r>=end)
        {
            if(p==1)
            return t[node];
            else
            return t1[node];
        }
        else
        {
            int m=(st+end)/2;
            
            if(p==1)
            return min( query(2*node+1,st,m,l,r,1), query(2*node+2,m+1,end,l,r,1));
            else
            return max( query(2*node+1,st,m,l,r,2), query(2*node+2,m+1,end,l,r,2));
        }
    }
}
int main()
{
    int q,x,y,i;
    cin>>n>>q;
    for(i=0;i<n;i++)
    cin>>a[i];
    build1(0,0,n-1);
    build2(0,0,n-1);
    while(q--)
    {
        cin>>x>>y;
        //y--;
        if(x==0)
        {
            int x1=query(0,0,n-1,y+1,n-1,1);
            int x2=query(0,0,n-1,0,y-1,2);
            
            if(x2<0)
            cout<<"-1"<<" ";
            else
            cout<<x2<<" ";
            
            if(x1>=n)
            cout<<"-1";
            else
            cout<<x1;
            
            cout<<endl;
        }
        else
        {
            if(a[y]==0){
            up1(0,0,n-1,y);
            up2(0,0,n-1,y);
            }
        }
    }
}
