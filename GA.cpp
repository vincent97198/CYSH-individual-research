#include<bits/stdc++.h>
#define N 100

using namespace std;

//設定隨機數生成器start
random_device rd;
auto tt = chrono::high_resolution_clock::now();
std::mt19937_64 gen = std::mt19937_64(tt.time_since_epoch().count());
std::uniform_int_distribution<> dis(0 , N);
auto randGenerator_shuffle = bind(dis , gen);
//設定隨機數生成器end

int n;
const int population=100,populationMin=10;
const double crossOverRate=0.7,mutationRate=0.1,generationMax=1000;

vector<int> TSP_order[population][2];	//一個存父代，一個存子代
vector<ll> G[N];
ll TSPdistance[population];

auto randShuffle(int x)
{
	return randGenerator_shuffle()%n;
}

void init()
{
	cin >> n;
	memset(TSPdistance,0,sizeof(TSPdistance));
/*
	int tmp;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cin >> tmp;
			if(tmp!=0)
				G[i].push_back(tmp);
			else
				G[i].push_back(1e17);
		}
	}
*/			
}

void randomlyGenerated()
{
	for(int i=0;i<population;++i){
		for(int j=0;j<n;++j)
			TSP_order[i][0].push_back(j);
		
		random_shuffle(TSP_order[i][0].begin(),TSP_order[i][0].end(),randShuffle);
`
		for(int j=1;j<n;++j)
			TSPdistance[i]+=G[TSP_order[i][j-1]][TSP_order[i][j]];
		TSPdistance[i]+=G[TSP_order[i][n-1]][TSP_order[i][0]];
	}
/*TEST
	for(int i=0;i<10;++i){
		cout << "number:" << i << endl;
		for(int j=0;j<n;++j)
			cout << TSP_order[i][j] << " ";
		cout << endl;
	}
*/
} 

int main()
{
	init();
	randomlyGenerated();
	
	int parent=0;
	queue<int> q;
	for(int genertaion=0;genertaion<generationMax;++generation){
		while()
	}

	return 0;
}
