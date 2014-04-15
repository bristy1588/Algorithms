/*
    Date : 15 April, 2014
    Suffix Array n(log n)^2
    Sample problem : Distinct Substrings 
*/
#include <stdio.h>
#include <bits/stdc++.h>
#define         MAXLG       17
#define         MAXN        100005
using namespace std;
typedef pair<int,int> pii;

struct node{
    int id, a[2];
};

bool cmp(node a, node b){
    if(a.a[0] != b.a[0]) return a.a[0]< b.a[0];
    return a.a[1] < b.a[1];
}
int P[MAXLG][MAXN],N;
// Finding the Longest Common Prefix.
int LCP(int x, int y){
    int i,ans;
    if(x == y) return N - x;
    ans =  0;

    for(i = 17; i >= 0; i--){
        if(((x + (1<<i)) > N) || ((y + (1<<i))> N)) continue;

        if(P[i][x] == P[i][y]){
            ans = ans + (1<<i);
            x = x + (1<<i);
            y = y + (1<<i);
        }
    }

    return ans;
}
string S;
node L[MAXN];
void DEEBUG()
{
       /// For Checking the contents of the suffix Array
        /*
        for(i = 0; i < N; i++){
            if( i != 0) printf(" ");
            printf("%d",P[j][i]);
        }
        printf("\n");
        */
        /// Checking the contents of L[i]
        /*
        for(i = 0; i < N; i++)
            printf("%d ", L[i].id);
        printf("\n");
        */
        return;
}

void SuffixArray(){
      // Suffix Array
    N = S.size();
    for(i = 0; i < N; i++)
        P[0][i] = S[i] - 'a';

    for(j = 1, cnt = 1 ; cnt >> 1 < N ;j++, cnt <<=1){
        for(i = 0; i < N ; i++){
            L[i].id = i;
            L[i].a[0] = P[j-1][i];
            if(i + cnt < N) L[i].a[1] = P[j-1][i+cnt];
            else L[i].a[1] = -1;
        }
        sort(L, L+ N, cmp);
        P[j][L[0].id] = 0;
        for(i = 1; i < N; i++){
            if(L[i].a[0] == L[i-1].a[0] && L[i].a[1] == L[i-1].a[1])
                P[j][L[i].id] = P[j][L[i-1].id];
            else P[j][L[i].id] = P[j][L[i-1].id] + 1;
        }
    }

    return;
}
int main(){

    int i,j,cnt;
    int T,tc,p,q,ans;

    cin >> T;
    tc = 0;
    while(tc<T){
        tc++;
    cin >> S;
    cin >> p >> q;

    SuffixArray();


        int x, y,len,now;
        ans = 0;
        for(i = 0; i < N; i++){
            len = min(N-i,q);
            ans = ans + max(0, len + 1 - p);

        }
          
          // Distinct Substring Problem
        int sub;
        for(i = 1; i < N; i++){
            now = min(LCP(L[i].id,L[i-1].id),q);
            sub = max(0,now+1 - p);
            ans-=sub;
           // printf("%d ",sub);
        }

        printf("Case %d: %d\n",tc,ans);
    }
    return 0;
}
