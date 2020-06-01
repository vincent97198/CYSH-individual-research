//預設定start
#include<bits/stdc++.h>	
#include <random>
#include <time.h>
#include <ratio>
#include <chrono>
#include <functional>

using namespace std;
//預設定end


//宣告變數
int n;

void input()	//輸入資料
{	
	cin >> n;	//input the number of cities
	cout << n << endl;
}

void solve()
{
	//設定隨機數生成器start
	random_device rd;
    auto tt = chrono::high_resolution_clock::now();
    std::mt19937_64 gen = std::mt19937_64(tt.time_since_epoch().count());
    std::uniform_int_distribution<> dis(0 , 10000);
    auto randfunction = bind(dis , gen);
	//設定隨機數生成器end

	for(int i=1;i<=n;++i){		//輸出n*n個隨機數
		for(int j=1;j<=n;++j){
			cout << randfunction() << " ";
		}
		cout << endl;
	}

}

int main()
{

	cout << "input the number of city:";
	FILE *fPtr=freopen("input_RAW.txt","a",stdout);	//開啟要寫入的檔案

	input();	//input data
	solve();	//output data

	fclose(fPtr);

    return 0;
}
