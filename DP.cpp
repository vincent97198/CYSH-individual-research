#include <bits/stdc++.h>
#define N 22
#define ll unsigned long long

using namespace std;

struct edge
{
	int to;
	ll cost;

	bool operator<(const edge &a)const{
		return cost>a.cost;
	}
};

int n,ROUTE[N][ ( (ll)1<<N ) ],start;
ll dp[N][ ( (ll)1<<N ) ],d[N],Path;
priority_queue<edge> q;
vector<edge> G[N];

void init()
{
	memset(dp,0x3f,sizeof(dp));

	for(int i=1;i<=n;++i)
		dp[i][0]=0;
	Path=(ll)1<<n;
}

void input()
{
	cin >> n;
	edge temporary;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			temporary.to=j;
			cin >> temporary.cost;
			G[i].push_back(temporary);
		}
	}
}

void solve()
{
	for (int i=1;i<( (ll)1<<n );++i){
		if (i==(i & Path)){
			memset(d,0x3f,sizeof(d));

			for (int j=1;j<=n;++j){

				if (!( ( 1 << (j-1) ) & i ))
					continue;
				d[j] = dp[j][i ^ ( 1 << (j-1) )];
				edge temporary;	temporary.cost = d[j];	temporary.to = j;
				q.push(temporary);
			}

			while (!q.empty()) {					//求從i走到任意點的最短距離
				edge now = q.top();	q.pop();

				for (edge E:G[now.to]) {
					if (( ( 1 << (E.to-1) ) & i ))		//要走到的點不能是i裡的
						continue;

					if (d[now.to]+E.cost<d[E.to]) {
						d[E.to]=d[now.to]+E.cost;
						ROUTE[E.to][i]=now.to;		//紀錄路徑
						edge temporary;	temporary.cost = d[E.to];	temporary.to = E.to;
						q.push(temporary);
					}
				}
			}
			for (int j=1; j<=n;j++)
				if (!( ( 1 << (j-1) ) & i ))		//要走到的點不能是i裡的
					dp[j][i] = d[j];
		}
	}

	ll MAX=(ll)1<<63;
	for(int i=1;i<=n;++i){
		if(dp[i][Path ^ ( 1 << (i-1) )]>MAX){
			MAX=dp[i][Path ^ ( 1 << (i-1) )];
			start=i;
		}
	}

}

void output()
{
	cout << "Minimum travel distance: " << dp[start][Path ^ ( 1 << (start-1) )]
		<< endl << "Travel route: ";

	int now = start;

	while (true) {
		cout << now << " ";
		if (Path & ( 1 << (now-1) ))			//通一個點可走多次
			Path ^= ( 1 << (now-1) );
		if (!Path)	break;
		now = ROUTE[now][Path];
	}
	cout << endl;
}

int main()
{
	FILE *fPtr=freopen("input_RAW.txt","r",stdin);

	input();
	init();
	solve();
	output();

	fclose(fPtr);

	return 0;
}
