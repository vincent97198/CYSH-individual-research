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
const int populationSize=1000,populationMin=10;
const double crossOverRate=0.9,mutationRate=0.1,filter=0.95;

vector<int> TSP_order[populationSize],G[N];

auto randShuffle(int x)
{
	return randGenerator_shuffle()%n;
}

void init()
{
	cin >> n;
/*
	int tmp;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cin >> tmp;
			G[i].push_back(tmp);
		}
	}
*/			
}

void randomlyGenerated()
{
	for(int i=0;i<populationSize;++i){
		for(int j=0;j<n;++j){
			TSP_order[i].push_back(j);
		}
		random_shuffle(TSP_order[i].begin(),TSP_order[i].end(),randShuffle);
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
	

	return 0;
}
