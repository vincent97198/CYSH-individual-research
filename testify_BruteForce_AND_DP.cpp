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
int n,t,num,tmp;

void solve()
{
	//設定隨機數生成器start
	random_device rd;
    auto tt = chrono::high_resolution_clock::now();
    std::mt19937_64 gen = std::mt19937_64(tt.time_since_epoch().count());
    std::uniform_int_distribution<> dis(-1000 , 10000);	// 約1/11的機率沒有邊
    auto randfunction = bind(dis , gen);
	//設定隨機數生成器end

	num=(abs(randfunction())%(n-1))+2;	//隨機一個城市數
	cout << num << endl;		//輸出程式數
	for(int i=1;i<=num;++i){		//輸出num*num個隨機數
		for(int j=1;j<=num;++j){
			tmp=randfunction();
			if(tmp<=0)	//若權重不大於0就當沒有那條邊
				tmp=0;
			cout << tmp << " ";
		}
		cout << endl;
	}

}

int main()
{
	cout << "input the number of test data:";
	cin >> t;	//輸入生成測資數
	cout << "\ninput the maximun of city:";
	cin >> n;

	//生成測資start
	FILE *fPtr=freopen("input_RAW.txt","w",stdout);	//開啟要寫入的檔案
	for(int i=0;i<t;++i)	//重複t次
		solve();	//output data
	fclose(fPtr);	//關閉測資檔案
	//生成測資end
	FILE *BruteForce=popen("./BruteForce","r");
	
	char trash=fgetc(BruteForce);
	int BruteForce_Ans[100000];

	for(int i=0;i<t;++i){
		fscanf(BruteForce,"ost: %d", &BruteForce_Ans[i]);
		do{
			trash=fgetc(BruteForce);
		}while(trash!='c' && trash!=EOF);
	}

	pclose(BruteForce);
	
	FILE *DP=popen("./DP","r");

	trash=fgetc(DP);
	int DP_Ans[100000];

	for(int i=0;i<t;++i){
		fscanf(DP,"ost: %d", &DP_Ans[i]);
		do{
			trash=fgetc(DP);
		}while(trash!='c' && trash!=EOF);
	}
	
	fclose(DP);
	
	freopen("result.txt","w",stdout);
	bool flag=true;
	int wrongLine;
	for(int i=0;i<t;++i){
		if(DP_Ans[i]!=BruteForce_Ans[i]){
			flag=false;
			wrongLine=i;
			break;
		}
	}
	if(flag)
		cout << "Correct" << endl;
	else
		cout << "Wrong" << endl << "wrong line: " << wrongLine <<  endl;

    return 0;
}


