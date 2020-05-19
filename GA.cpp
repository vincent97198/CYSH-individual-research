#include<bits/stdc++.h>
#define ll long long
#define N 100000

using namespace std;
//呼叫執行程式所需的相關檔案
//設定隨機數生成器start
random_device rd;
auto tt = chrono::high_resolution_clock::now();
std::mt19937_64 gen = std::mt19937_64(tt.time_since_epoch().count());
std::uniform_real_distribution<> dis(0 , 1);
auto randGenerator = bind(dis , gen);
//設定隨機數生成器end

int n;	//城市數
const int population=10000;	//族群大小
const long double crossOverRate=0.8,mutationRate=0.01,generationMax=10000;	//交配率為0.8,突變率為0.01,最大世代數為10000

vector< vector<int> > TSP_order;	//儲存所有個體的基因
vector<long double> G[N];		//儲存路徑圖
vector<long double> TSPdistance;	//儲存每個個體的花費
long double TSPdistanceMAX=0;	//儲存所有路徑花費的總和

auto randShuffle(int x)	//製造一個小於x的非負亂數
{
    return (int)(randGenerator()*1e8)%x;
}

bool cmp(int a,int b)	//排序的比較函數
{
    if(TSPdistance[a]<TSPdistance[b])	//若TSPdistance[a]<TSPdistance[b]則讓a排在b前面
        return true;
    else
        return false;
}

void init()	//初始化所有變數
{
    TSP_order.clear();	//確保一開始沒有任何個體
    TSPdistance.clear();	//清空TSPdistance

    int tmp;
    for(int i=0;i<n;++i){	//輸入表示路徑的矩陣，並儲存
        G[i].clear();	//在使用前先清空
        for(int j=0;j<n;++j){
            cin >> tmp;
            G[i].push_back(tmp);	//放入儲存資料
            TSPdistanceMAX+=tmp;	//紀錄所有路徑的花費
        }
    }
}

void randomlyGenerated()	//隨機生成個體
{
    vector<int> ordinaryOrder;	//暫存個體的基因
    for(int i=0;i<n;++i)
        ordinaryOrder.push_back(i);	//初始化為1,2,3...n基因的個體

    for(int i=0;i<population;++i){
        TSP_order.push_back(ordinaryOrder);	//放入族群中
        random_shuffle(TSP_order[i].begin(),TSP_order[i].end(),randShuffle);	//打亂剛剛放入族群中的個體的基因（變成隨機的基因）

        long double tmpDistance=G[TSP_order[i][n-1]][TSP_order[i][0]];	//暫存剛剛個體的花費
        for(int j=1;j<n;++j)
            tmpDistance+=G[TSP_order[i][j-1]][TSP_order[i][j]];	//計算剛剛個體的花費
        TSPdistance.push_back(tmpDistance);		//將計算結果存起來
    }
}

void crossOver(int father,int mother)	//交換（採用Partially Mapped Crossover Operator）
{
	/*
	example:
		P1 = (3 4 8 2 7 1 6 5)
		P2 = (4 2 5 1 6 8 3 7)
	*/

    int crossPoint1=randShuffle(n),crossPoint2=randShuffle(n);	//隨機選取基因上兩點
    if(crossPoint2<crossPoint1)		//確保選取兩點crossPoint1>crossPoint2
        swap(crossPoint1,crossPoint2);

	/*
	   以 | 代表基因的切割點
	example:
		P1 = (3 4 8 2 7 1 6 5)
		P2 = (4 2 5 | 1 6 8 | 3 7)
	*/

    vector<int> tmp;	//暫存下一代的基因
    set<int> needToRemove;
    for(int i=crossPoint1;i<=crossPoint2;++i)	//將mother的第crossPoint1個到第crossPoint2個基因選出來
        needToRemove.insert(TSP_order[mother][i]);
	/*
	   建構後代基因型
	   C = (× × × | 1 6 8 | × ×)
	   P1 = (3 4 x 2 7 x x 5)
	*/
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

	/*
	   依序填入P1的基因到C裡面
	   C = (3 4 2 | 1 6 8 | 7 5)
	   將C放入族群中
	*/

    if(COUNT==crossPoint1){	
        for(int j=crossPoint1;j<=crossPoint2;++j)
            tmp.push_back(TSP_order[mother][j]);
    }
    TSP_order.push_back(tmp);
}

void mutation(int num)	//突變
{
	/*
	   P = (1 3 5 4 6 7 8)
	*/
    vector<int> tmp;	//暫存突變後的基因

    int a=randShuffle(n),b=randShuffle(n);	//隨機兩個城市（核苷酸）
    while(b==a){
        b=randShuffle(n);
    }

	/*
	   P = (1 3 5 4 6 7 8)
	   a=3
	   b=7
	*/
	

    for(int i=0;i<n;++i){	//尋找兩城市（核苷酸）的位置並交換
        if(TSP_order[num][i]==a)
            tmp.push_back(b);
        else if(TSP_order[num][i]==b)
            tmp.push_back(a);
        else
            tmp.push_back(TSP_order[num][i]);
    }
	/*
	   突變後的個體
	   Q =(1 7 5 4 6 3 8)
	*/
    TSP_order.push_back(tmp);
}

int main()
{
    //freopen("input_RAW.txt","r",stdin);
	cout << fixed << setprecision(6);	//設定輸出精度到小數點下六位
    while(cin >> n){	//輸入城市數

        init();		//執行初始化
        randomlyGenerated();	//生成初始個體

        long double distanceSum[population],MIN0=1e18;

		for(int i=0;i<population;++i)		//紀錄隨機生成的初始個體的最小值
			MIN0=min(MIN0,TSPdistance[i]);
		cout << MIN0 << endl;

        ll t=0,num;
        for(int generation=0;generation<generationMax;++generation){	//重複數代
            memset(distanceSum,0,sizeof(distanceSum));	//清空機率輪盤
            for(int i=1;i<population;++i)
                distanceSum[i]=TSPdistanceMAX-TSPdistance[i-1]+distanceSum[i-1];	//計算每個個體的適應值，適應值=所有路徑花費-個體花費
            for(int i=0;i<population;++i)		//設定機率輪盤
                distanceSum[i]/=distanceSum[population-1];

            for(int i=0;i<population;++i){
                if(randGenerator()<=crossOverRate){		//對於每一個個體若可以交換（交換率決定）
                    long double Probability=randGenerator();	//透過機率輪盤決定交換對象
                    int pos=distance(distanceSum,lower_bound(distanceSum,distanceSum+population,Probability));
                    crossOver(i,pos);
                }
            }

            for(int i=0;i<population;++i)	//對每一個個體（不含剛交換後的下一代）決定是否突變（由突變率決定）
                if(randGenerator()<=mutationRate)
                    mutation(i);

            for(int i=population;i<TSP_order.size();++i){		//計算新產生的個體的花費（突變與交換）
                ll tmpDistance=G[TSP_order[i][n-1]][TSP_order[i][0]];
                for(int j=1;j<TSP_order[i].size();++j)
                    tmpDistance+=G[TSP_order[i][j-1]][TSP_order[i][j]];
                TSPdistance.push_back(tmpDistance);
            }

            vector<int> index;		//自然淘汰：將花費前population小的個體保留，其他淘汰------start
            for(int i=0;i<TSP_order.size();++i)
                index.push_back(i);

            sort(index.begin(),index.end(),cmp);
            index.erase(index.begin(),index.begin()+population);
            sort(index.begin(),index.end());

            for(int i=0;i<index.size();++i){
                TSP_order.erase(TSP_order.begin()+index[i]-i);
                TSPdistance.erase(TSPdistance.begin()+index[i]-i);
            }		//自然淘汰------end

            long double min0=1e18;		//紀錄所有個體的花費最小值
            for(int i=0;i<population;++i){
                if(min0>TSPdistance[i]){
                    min0=TSPdistance[i];
                    num=i;
                }
            }
			MIN0=min(MIN0,min0);
			cout << MIN0 << endl;	//輸出每代的最小值
        }
        cout << "cost: " << MIN0 << endl;	//輸出運算最終的最小花費
		/*		//除錯用，輸出路徑
        for(int i=0;i<n;++i)
        	cout << TSP_order[num][i]+1 << "->";
        cout << TSP_order[num][0]+1 << endl;
		*/
    }
    return 0;
}

