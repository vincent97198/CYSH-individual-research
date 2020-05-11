#include<bits/stdc++.h>
#define ll long long
#define N 100000

using namespace std;

//設定隨機數生成器start
random_device rd;
auto tt = chrono::high_resolution_clock::now();
std::mt19937_64 gen = std::mt19937_64(tt.time_since_epoch().count());
std::uniform_real_distribution<> dis(0 , 1);
auto randGenerator = bind(dis , gen);
//設定隨機數生成器end

int n;
const int population=10000;
const long double crossOverRate=0.8,mutationRate=0.01,generationMax=50000;

vector< vector<int> > TSP_order;
vector<long double> G[N];
vector<long double> TSPdistance;
long double TSPdistanceMAX=0;

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
    TSP_order.clear();
    TSPdistance.clear();

    int tmp;
    for(int i=0;i<n;++i){
        G[i].clear();
        for(int j=0;j<n;++j){
            cin >> tmp;
            if(tmp!=0){
                G[i].push_back(tmp);
                TSPdistanceMAX+=tmp;
            }
            else{
                G[i].push_back(1e15);
                TSPdistanceMAX+=1e15;
            }
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

        long double tmpDistance=G[TSP_order[i][n-1]][TSP_order[i][0]];
        for(int j=1;j<n;++j)
            tmpDistance+=G[TSP_order[i][j-1]][TSP_order[i][j]];
        TSPdistance.push_back(tmpDistance);
    }
}

void crossOver(int father,int mother)
{
    int crossPoint1=randShuffle(n),crossPoint2=randShuffle(n);
    if(crossPoint2<crossPoint1)
        swap(crossPoint1,crossPoint2);

    vector<int> tmp;
    set<int> needToRemove;
    for(int i=crossPoint1;i<=crossPoint2;++i)
        needToRemove.insert(TSP_order[mother][i]);

    int COUNT=0;
    for(int i=0;i<n;++i){
        if(COUNT==crossPoint1){
            for(int j=crossPoint1;j<=crossPoint2;++j)
                tmp.push_back(TSP_order[mother][j]);
            ++COUNT;
        }
        if(needToRemove.find(TSP_order[father][i])==needToRemove.end()){
            tmp.push_back(TSP_order[father][i]);
            ++COUNT;
        }
    }

    if(COUNT==crossPoint1){
        for(int j=crossPoint1;j<=crossPoint2;++j)
            tmp.push_back(TSP_order[mother][j]);
    }
    TSP_order.push_back(tmp);
}

void mutation(int num)
{
    vector<int> tmp;

    int a=randShuffle(n),b=randShuffle(n);
    while(b==a){
        b=randShuffle(n);
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
    //freopen("input_RAW.txt","r",stdin);
	cout << fixed << setprecision(6);
    while(cin >> n){
        auto t1=clock();

        init();
        randomlyGenerated();

        long double distanceSum[population],MIN0=1e18;

		for(int i=0;i<population;++i)
			MIN0=min(MIN0,TSPdistance[i]);
		cout << MIN0 << endl;

        ll t=0,num;
        for(int generation=0;generation<generationMax;++generation){
            memset(distanceSum,0,sizeof(distanceSum));
            for(int i=1;i<population;++i)
                distanceSum[i]=TSPdistanceMAX-TSPdistance[i-1]+distanceSum[i-1];
            for(int i=0;i<population;++i)
                distanceSum[i]/=distanceSum[population-1];

            for(int i=0;i<population;++i){
                if(randGenerator()<=crossOverRate){
                    long double Probability=randGenerator();
                    int pos=distance(distanceSum,lower_bound(distanceSum,distanceSum+population,Probability));
                    crossOver(i,pos);
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
            index.erase(index.begin(),index.begin()+population);
            sort(index.begin(),index.end());

            for(int i=0;i<index.size();++i){
                TSP_order.erase(TSP_order.begin()+index[i]-i);
                TSPdistance.erase(TSPdistance.begin()+index[i]-i);
            }

            long double min0=1e18;
            for(int i=0;i<population;++i){
                if(min0>TSPdistance[i]){
                    min0=TSPdistance[i];
                    num=i;
                }
            }
			MIN0=min(MIN0,min0);
			cout << MIN0 << endl;
        }
        auto t2=clock();
        if(MIN0<=1e12)
            cout << "cost: " << MIN0 << endl;
        else
            cout << "cost: 0\n";
        cout << "TIME: " << (t2-t1)/(double)CLOCKS_PER_SEC << endl <<  "Travel route: ";
		/*
        for(int i=0;i<n;++i)
        	cout << TSP_order[num][i]+1 << "->";
        cout << TSP_order[num][0]+1 << endl;
		*/
    }
    return 0;
}

