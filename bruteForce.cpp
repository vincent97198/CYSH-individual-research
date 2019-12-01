//預設定start
#include<bits/stdc++.h>			

#define ll long long
#define MAXN 50

using namespace std;
//預設定end

struct edge{
	ll to,cost;	//目的地，路程花費
};

//宣告變數
ll n,ans=(ll)1<<61;	//儲存 節點數 當前最佳解
bool visit[MAXN];	//紀錄節點是否走過
vector<int> route,temporaryRoute(MAXN);	//儲存最佳解路徑 儲存當前遞迴路徑（初始化大小為MAXN，意即節點數的上限）
vector<edge> E[MAXN];	//邊 index代表起始位置

void dfs(int now,ll COST,int node,int start)	//遞迴路徑的函數，有分個變數分別代表 現在位置,當前花費,剩下幾個節點沒走過,起點
{
	if(node==0){	//走過每個城市一次
		bool flag=false;
		for(int i=0;i<E[now].size();++i){	//判斷最後能不能走回起點
			if(E[now][i].to==start){
				flag=true;
				COST+=E[now][i].cost;
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
	for(int i=0;i<E[now].size();++i){	//窮舉與now相連的邊
		next=E[now][i].to;
		if(!visit[next]){	//確定是沒走過的點
			temporaryRoute[node-1]=next;	//紀錄遞迴路徑
			visit[next]=true;	//標記next已經走到了
			dfs(next,COST+E[now][i].cost,node-1,start);	//進入下一層遞迴
			visit[next]=false;	//因為離開遞迴了，所以可以變回原本的狀態
		}
	}
}

void input()	//輸入資料
{	

	edge temporary;
	for(int from=1;from<=n;++from){	//輸入邊的資料
		for(int j=1;j<=n;++j){
			temporary.to=j;
			cin >> temporary.cost;
			E[from].push_back(temporary);
		}
	}
}

void solve()	//calculate the answer
{
	memset(visit,0,sizeof(visit));	//初始化visit，使visit全部為false
	for(int start=1;start<=n;++start){	//窮舉起始位置
		temporaryRoute[n-1]=start;	//紀錄起點
		visit[start]=true;	//標記起點已走過
		dfs(start,0,n-1,start);	//計算以start為起點的最短迴路
		visit[start]=false;	//恢復起點標記
	}

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
		input();	//input data
		solve();	//output data
	}

	fclose(fPtr);	//關閉讀取的檔案

    return 0;
}

