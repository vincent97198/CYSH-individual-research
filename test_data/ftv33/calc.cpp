#include <bits/stdc++.h>
using namespace std;
int main()
{
	long double now,ans=2020;
	cout << fixed << setprecision(5);
	int t=0;
	while(cin >> now){
		t++;
		cout << (now-ans)/ans << endl;
	}
	for(;t<10000;++t)
		cout << 0.0000 << endl;
}
