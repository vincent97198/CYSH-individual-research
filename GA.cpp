#include<bits/stdc++.h>
#define ll long long
#define N 100

using namespace std;

//設定隨機數生成器start
random_device rd;
auto tt = chrono::high_resolution_clock::now();
std::mt19937_64 gen = std::mt19937_64(tt.time_since_epoch().count());
std::uniform_real_distribution<> dis(0 , 1);
auto randGenerator = bind(dis , gen);
//設定隨機數生成器end

int n;
const int population=5;
const double crossOverRate=0.9,mutationRate=0.1,generationMax=1000;

vector< vector<int> > TSP_order;
vector<ll> G[N];
vector<ll> TSPdistance;

auto randShuffle(int x)
{
	return (int)(randGenerator()*1e8)%x;
}

bool cmp(int a,int b)
{
	if(TSPdistance[a]<TSPdistance[b])
		return true;
	else
		return false;
}

void init()
{
	cin >> n;

	int tmp;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cin >> tmp;
			if(tmp!=0)
				G[i].push_back(tmp);
			else
				G[i].push_back(1e12);
		}
	}	
}

void randomlyGenerated()
{
	vector<int> ordinaryOrder;
	for(int i=0;i<n;++i)
		ordinaryOrder.push_back(i);

	for(int i=0;i<population;++i){
		TSP_order.push_back(ordinaryOrder);
		random_shuffle(TSP_order[i].begin(),TSP_order[i].end(),randShuffle);

		ll tmpDistance=G[TSP_order[i][n-1]][TSP_order[i][0]];
		for(int j=1;j<n;++j)
			tmpDistance+=G[TSP_order[i][j-1]][TSP_order[i][j]];
		TSPdistance.push_back(tmpDistance);
	}
}

void crossOver(int father,int mother)
{
	int crossPoint=randShuffle(n-1)+1;
	vector<int> tmp1,tmp2;
	set<int> needToRemove;
	for(int i=crossPoint;i<n;++i)
		needToRemove.insert(TSP_order[mother][i]);

	for(int i=0;i<crossPoint;++i)
		if(needToRemove.find(TSP_order[father][i])==needToRemove.end())
			tmp1.push_back(TSP_order[father][i]);
	for(int i=crossPoint;i<n;++i)
		tmp1.push_back(TSP_order[mother][i]);
}

void mutation(int num)
{
	vector<int> tmp;

	int a=randShuffle(N+1),b=randShuffle(N+1);
	while(b==a){
		b=randShuffle(N+1);
	}

	for(int i=0;i<n;++i){
		if(TSP_order[num][i]==a)
			tmp.push_back(b);
		else if(TSP_order[num][i]==b)
			tmp.push_back(a);
		else
			tmp.push_back(TSP_order[num][i]);
	}
	TSP_order.push_back(tmp);
}

int main()
{
	init();
	randomlyGenerated();
	
	double distanceSum[population];
	for(int generation=0;generation<generationMax;++generation){
		memset(distanceSum,0,sizeof(distanceSum));
		for(int i=1;i<population;++i)
			distanceSum[i]=TSPdistance[i-1]+distanceSum[i-1];
		for(int i=0;i<population;++i)
			distanceSum[i]/=distanceSum[population-1];

		for(int i=0;i<population;++i){
			if(randGenerator()<=crossOverRate){
				TSP_order.push_back(TSP_order[i]);
				double Probability=randGenerator();
				int pos=distance(distanceSum,lower_bound(distanceSum,distanceSum+population,Probability));
				crossOver(TSP_order.size()-1,pos);
			}
		}
		
		for(int i=0;i<population;++i)
			if(randGenerator()<=mutationRate)
				mutation(i);

		for(int i=population;i<TSP_order.size();++i){
			ll tmpDistance=G[TSP_order[i][n-1]][TSP_order[i][0]];
			for(int j=1;j<TSP_order[i].size();++j)
				tmpDistance+=G[TSP_order[i][j-1]][TSP_order[i][j]];
			TSPdistance.push_back(tmpDistance);
		}

		vector<int> index;
		for(int i=0;i<TSP_order.size();++i)
			index.push_back(i);

		sort(index.begin(),index.end(),cmp);

		for(int i=population;i<index.size();++i){
			TSP_order.erase(TSP_order.begin()+index[i]);
			TSPdistance.erase(TSPdistance.begin()+index[i]);
		}
	/*		
		for(int i=population;i<TSP_order.size();++i){
			cout << "number:" << i << endl;
			for(int j=0;j<n;++j)	
				cout << TSP_order[i][j] << " ";
			cout << endl;
		}	
	*/
	}

	return 0;
}
