/*
    Date        :   Jan 23, 2014
    Note        :   My First Flow Algorithm
    Algorithm   :   Ford - Fulkerson Method
    Problem     :   Light OJ 1153 - Internet Bandwidth
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#define     inf     1000000009
#define     z       105
using namespace std;
bool vis[z];
int v[z][z], par[z];
int N,S,T,C;

int Find_Flow()
{
    queue<int> q;

    memset(vis, 0, sizeof(vis));
    memset(par, -1 , sizeof(par));

    vis[S] = true;
    q.push(S);
    int cur,i;

    while(!q.empty()){

        cur = q.front(); q.pop();
        if(cur == T) break;
        for(i = 0; i < N; i++){
            if(v[cur][i]==0 || vis[i] == true) continue;
            vis[i] = true;
            par[i] = cur;
            q.push(i);
        }

    }

    int now, cap;

    now = T;
    cap = inf;
    while(par[now]> -1){
        cur = par[now];
        cap = min(cap, v[cur][now]);
        now = cur;
    }
    now = T;
    while(par[now] > -1){
        cur = par[now];
        v[cur][now] -=cap;
        v[now][cur] +=cap;
        now = cur;
    }

    if(cap==inf) cap = 0;
    return cap;
}


int max_flow()
{
    int ans, flow;

   ans = 0;
    while(1){
        flow = Find_Flow();
        if(flow==0) break;
        ans+= flow;
    }
    return ans;
}

int main()
{
    int t,tc,a,b,d,i;

    cin >> t;
    tc = 0;

    while(tc<t){
        tc++;

        cin>>N;
        cin>>S>>T>>C;
        S--; T--;

        memset(v, 0 , sizeof(v));
        for(i = 0; i < C; i++){
            cin >> a>> b>> d;
            a--; b--;
            v[a][b] += d;
            v[b][a] += d;
        }

       int ans = max_flow();

        printf("Case %d: %d\n",tc, ans);


    }
    return 0;
}
