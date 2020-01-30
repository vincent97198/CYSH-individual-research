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
    std::uniform_int_distribution<> dis(-100 , 1000);	// 約1/11的機率沒有邊
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
	
	FILE *GA=popen("./GA","r");
	
	char trash=fgetc(GA);
	int GA_Ans[100000];
	double GA_Time[100000];

	for(int i=0;i<t;++i){
		fscanf(GA,"ost: %d\n", &GA_Ans[i]);
		fscanf(GA,"TIME: %lf",&GA_Time[i]);
		do{
			trash=fgetc(GA);
		}while(trash!='c' && trash!=EOF);
	}

	pclose(GA);
	
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

	double deviation[100000],MAX0=0,MIN0=100000,sum=0,TIME_MAX0=0,TIME_MIN0=100000,TIME_sum=0,SD=0;

	for(int i=0;i<t;++i){
		if(DP_Ans[i]==0){
			if(GA_Ans[i]==0)
				continue;
			else{
				cout << "wrong\n";
				break;
			}
		}
	
		deviation[i]=(GA_Ans[i]-DP_Ans[i])/(double)DP_Ans[i];
		sum+=deviation[i];
		SD+=pow(deviation[i],2)/t;
		TIME_sum+=GA_Time[i];
		TIME_MAX0=max(TIME_MAX0,GA_Time[i]);
		TIME_MIN0=min(TIME_MIN0,GA_Time[i]);
		MAX0=max(MAX0,deviation[i]);
		MIN0=min(MIN0,deviation[i]);
	}

	SD-=pow(sum/t,2);
	SD=sqrt(SD);
	cout << fixed << setprecision(5);
	cout << "Average deviation: " << sum/t << "%" << endl;
	cout << "Standard deviation: " << SD << endl;
	cout << "Average Time: " << TIME_sum/t << " seconds" << endl;
	cout << "MAX deviation:" << MAX0 << "%" << endl << "min deviation: " << MIN0 << "%" << endl;
	cout << "MAX TIME: " << TIME_MAX0 << " seconds" << endl << "min TIME: " << TIME_MIN0 << " seconds" << endl << endl;

	for(int i=0;i<t;++i)
	cout << "Case: " << i+1 << endl <<"GA_Ans: " << GA_Ans[i] << "   TIME: " << GA_Time[i]  << "\nDP_Ans: " << DP_Ans[i] << "\ndeviation: " << deviation[i] << "%" << endl << endl;

    return 0;
}


