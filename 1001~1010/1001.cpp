//
// Created by 肖龙 on 2019-03-05.
//

#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#define MAXX 4000010
using namespace std;

int n,m,ge;

int fir[MAXX],nex[MAXX*2],w[MAXX*2],v[MAXX*2],anss;

int read(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')
        ch=getchar();
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}
void link(int x,int y,int va){
    anss++;
    w[anss]=y;
    v[anss]=va;
    nex[anss]=fir[x];
    fir[x]=anss;
    anss++;
    w[anss]=x;
    v[anss]=va;
    nex[anss]=fir[y];
    fir[y]=anss;
}


void init(){
    n=read();
    m=read();
    ge=(n-1)*(m-1);
    int temp;
    memset(fir,-1,sizeof(fir));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m-1;j++){
            temp=read();
            if(i==1){
                link(ge*2+1,(i-1)*(m-1)+j,temp);
            }
            else if(i==n){
                link((i-2)*(m-1)+j+ge,ge*2+2,temp);
            }
            else link((i-1)*(m-1)+j,(i-2)*(m-1)+j+ge,temp);
        }
    }
    for(int i=1;i<=n-1;i++){
        for(int j=1;j<=m;j++){
            temp=read();
            if(j==1){
                link((i-1)*(m-1)+j+ge,ge*2+2,temp);
            }
            else if(j==m){
                link((i-1)*(m-1)+j-1,ge*2+1,temp);
            }
            else {
                link((i-1)*(m-1)+j+ge,(i-1)*(m-1)+j-1,temp);
            }
        }
    }
    for(int i=1;i<=n-1;i++){
        for(int j=1;j<=m-1;j++){
            temp=read();
            link((i-1)*(m-1)+j,(i-1)*(m-1)+j+ge,temp);
        }
    }
}

int dis[MAXX],book[MAXX];

int spfa(int x,int y){
    memset(dis,-1,sizeof(dis));
    dis[x]=0;
    queue<int> q1;
    q1.push(x);
    book[x]=1;
    while(!q1.empty()){
        int dd=q1.front();
        q1.pop();
        book[dd]=0;
        for(int i=fir[dd];i!=-1;i=nex[i]){
            if(dis[w[i]]==-1||dis[w[i]]>dis[dd]+v[i]){
                dis[w[i]]=dis[dd]+v[i];
                if(book[w[i]]==0){
                    book[w[i]]=1;
                    q1.push(w[i]);
                }
            }
        }
    }
    return dis[y];
}
int main(){
    init();
    cout<<spfa(ge*2+1,ge*2+2)<<endl;
    return 0;
}