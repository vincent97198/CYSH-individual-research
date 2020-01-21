//預設定start
#include<bits/stdc++.h>			

#define ll long long
#define MAXN 50

using namespace std;
//預設定end


//宣告變數
ll n,ans=(ll)1<<61;	//儲存 節點數 當前最佳解
bool visit[MAXN];	//紀錄節點是否走過
vector<int> route,temporaryRoute(MAXN);	//儲存最佳解路徑 儲存當前遞迴路徑（初始化大小為MAXN，意即節點數的上限）
vector<int> E[MAXN];	//存邊 index代表起始位置

void dfs(int now,ll COST,int node,int start)	//遞迴路徑的函數，有分個變數分別代表 現在位置,當前花費,剩下幾個節點沒走過,起點
{
	if(COST>ans)	//若當前結果已大於之前求得的最小值則該路徑不可能是最佳路徑，所以跳出此路徑
		return;
	if(node==0){	//走過每個城市一次
		bool flag=false;
		for(int i=0;i<n;++i){	//判斷最後能不能走回起點
			if(E[now][i]!=0){
				flag=true;
				COST+=E[now][i];
				break;
			}
		}

		if(!flag)	//找不到回起點的路，所以重新找路
			return;	//跳出該層遞迴

		if(COST<ans){	//找到路徑，比較當前路徑的花費與當前找到的最小值
			ans=COST;
			route.clear();	//清空紀錄器
			for(int i=0;i<n;++i)	//紀錄下最佳路徑
				route.push_back(temporaryRoute[i]);
		}
		return;	//跳出該層遞迴
	}

	int next;	//存放下一個節點
	for(int i=0;i<n;++i){	//窮舉下一個點
		next=i+1;
		if(E[now][i]==0)	//若連線邊不存在
			continue;
		if(!visit[next]){	//確定是沒走過的點
			temporaryRoute[node-1]=next;	//紀錄遞迴路徑
			visit[next]=true;	//標記next已經走到了
			dfs(next,COST+E[now][i],node-1,start);	//進入下一層遞迴
			visit[next]=false;	//因為離開遞迴了，所以可以變回原本的狀態
		}
	}
}

void init()
{
	ans=(ll)1<<61;
	route.clear();
	temporaryRoute.clear();
	memset(visit,0,sizeof(visit));
	for(int i=1;i<=n;++i)
		E[i].clear();
}

void input()	//輸入資料
{	
	int temporaryCOST;
	for(int from=1;from<=n;++from){	//輸入邊的資料
		for(int j=1;j<=n;++j){
			cin >> temporaryCOST;
			E[from].push_back(temporaryCOST);
		}
	}
}

void solve()	//calculate the answer
{
	memset(visit,0,sizeof(visit));	//初始化visit，使visit全部為false
	int start=1;
	temporaryRoute[n-1]=start;	//紀錄起點
	visit[start]=true;	//標記起點已走過
	dfs(start,0,n-1,start);	//計算以start為起點的最短迴路

	cout << "cost: " << ans << endl;	//輸出答案

	cout << "route: ";
	for(int i=n-1;i>=0;--i)	//輸出最佳解路徑（若有多條僅輸出其中一條）
		cout << route[i] << "->";
	cout << route[n-1] << endl;
}

int main()
{
	FILE *fPtr=freopen("input_RAW.txt","r",stdin);	//開啟要讀取的檔案
	
	while(cin >> n){//輸入n
		init();		//初始化
		input();	//input data
		solve();	//output data
	}

	fclose(fPtr);	//關閉讀取的檔案

    return 0;
}

