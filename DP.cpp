#include <bits/stdc++.h>
#define N 22
#define ll long long

using namespace std;

int n;
vector<int> G[N];
int dp[N][(ll)1<<N],NEXTPOS[N];

void init()
{
	for(int i=0;i<n;++i){
		G[i].clear();
		NEXTPOS[i]=i;
	}
    memset(dp,0x3f,sizeof(dp));

    dp[0][1]=0;
}

void input()
{
    int temporaryCOST;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cin >> temporaryCOST;
            G[i].push_back(temporaryCOST);
        }
    }
}

void solve()
{
    for(ll path=1;path<((ll)1<<(n));++path){
        for(int next=1;next<n;++next){
            if( ((ll)1<<next)&path )    continue;
                for(int FROM=0;FROM<n;++FROM) {
                    if ( ((ll) 1 << FROM) & path && (dp[next][path + ((ll) 1 << next)]>( dp[FROM][path] + G[FROM][next])) ) {
                        NEXTPOS[FROM]=next;
                        dp[next][path + ((ll) 1 << next)]= dp[FROM][path] + G[FROM][next];
                    }
                }
        }
    }
}

void output()
{
    int ans=1e9;
    for(int FROM=0;FROM<n;++FROM)
        ans=min(dp[FROM][((ll)1<<(n))-1]+G[FROM][0],ans);
    cout << "Minimun travel distance:  " << ans << endl << "Travel route: ";

    for(int now=0,t=0;t<n;++t,now=NEXTPOS[now]){
        cout << now+1 << "->";
    }
    cout << 1 << endl;
}

int main()
{
    FILE *fPtr=freopen("input_RAW.txt","r",stdin);

	while(cin >> n){
   		init();
   	    input();
   		solve();
		output();
	}

    fclose(fPtr);

    return 0;
}

