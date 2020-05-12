#include <bits/stdc++.h>
using namespace std;
int main()
{
	long double now,pre,ans=1839;
	cout << fixed << setprecision(5);
	int t=0;
	while(cin >> now){
		t++;
		pre=now;
		cout << (now-ans)/ans << endl;
	}
	for(;t<10000;++t)
		cout << (pre-ans)/ans << endl;
}
