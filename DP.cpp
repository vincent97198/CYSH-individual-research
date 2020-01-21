#include <bits/stdc++.h>
#define N 22
#define ll long long

using namespace std;

int n;
vector<int> G[N];
int dp[N][(ll)1<<N],NEXTPOS[N];	//dp[若為i表示目前在i+1點][走過的路徑，二進位下第i位為1表示第i+1點有走過，0表示未走過]

void init()	//初始化，清除上次的運算結果
{
	for(int i=0;i<n;++i){	
		G[i].clear();
		NEXTPOS[i]=i;
	}
    memset(dp,0x3f,sizeof(dp));	

    dp[0][1]=0;	//最後結果必為環形，故直接假設由1為起始點，
}

void input()	//輸入資料
{
    int temporaryCOST;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cin >> temporaryCOST;
            G[i].push_back(temporaryCOST);	//將花費存成邊的權重
        }
    }
}

void solve()
{
    for(ll path=1;path<((ll)1<<(n));++path){	//窮舉經歷過的路徑
        for(int next=1;next<n;++next){			//窮舉下一個要走的點
            if( ((ll)1<<next)&path )    continue;	//確定next不是走過的點
                for(int FROM=0;FROM<n;++FROM) {	//窮舉經歷過的點裡，是由那一個連向next
					if(G[FROM][next]==0)	//若連線不存在，則跳過
						continue;
                    if ( ((ll) 1 << FROM) & path && (dp[next][path + ((ll) 1 << next)]>( dp[FROM][path] + G[FROM][next])) ) {	//確定FROM真的走過（在path裡），且若由FROM連到next形成的路徑圖會是比之前的好，就更新 最小權重和 與 連線方式(NESTPOS[])
                        NEXTPOS[FROM]=next;	//紀錄FROM連向next會是更佳的連線方式
                        dp[next][path + ((ll) 1 << next)]= dp[FROM][path] + G[FROM][next];	//紀錄下此連線方式的權重和
                    }
                }
        }
    }
}

void output()
{
    int ans=1e9;
    for(int FROM=0;FROM<n;++FROM)	//窮舉由那一個點連回起始點會有最佳結果
        ans=min(dp[FROM][((ll)1<<(n))-1]+G[FROM][0],ans);	
    cout << "cost: " << ans << endl << "Travel route: ";	//輸出值

    for(int now=0,t=0;t<n;++t,now=NEXTPOS[now]){	//輸出路徑結果
        cout << now+1 << "->";
    }
    cout << 1 << endl;	//最後必連回起始點
}

int main()
{
    FILE *fPtr=freopen("input_RAW.txt","r",stdin);	//開啟輸入資料的檔案

	while(cin >> n){
   		init();
   	    input();
   		solve();
		output();
	}

    fclose(fPtr);	//關閉輸入資料的檔案

    return 0;
}

