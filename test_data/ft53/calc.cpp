#include <bits/stdc++.h>
using namespace std;
int main()
{
	long double now,ans=6905;
	cout << fixed << setprecision(5);
	for(int i=0;i<10000;++i){
		cin >> now;
		cout << (now-ans)/ans << endl;
	}
}
