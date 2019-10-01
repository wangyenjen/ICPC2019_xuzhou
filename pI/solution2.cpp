#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
using namespace std;
#define IOS {cin.tie(0);ios_base::sync_with_stdio(false);}
#define int int64_t
#define N 300000

multiset<pair<int,int> > s,s2,s3;
multiset<int> sb;
int32_t main(){
	IOS;
	int n,a,b,ans = INT_MAX;
	cin >> n;
	for(int i=0;i<n;i++){
		cin >> a >> b;
		s.insert({a,b});
		s2.insert({b,a});
		sb.insert(b);
	}
	for(int i=0;i<n-1;i++){
		//cout << i << ' ' << s2.size << ' ' << s.size() << ' ' << sb.size() << '\n';
		auto it = *--s.end();
		auto it2 = *--s2.end();
		//cout << complex<int>(it2.first,it2.second) << ' ';
		sb.erase(sb.find(it2.first));
		int f2 = it2.second - (*--sb.end());
		sb.insert(it2.first);
		sb.erase(sb.find(it.second));
		int f1 = it.first - (*--sb.end());
		sb.insert(it.second);
		//cout << complex<int>(f1,f2) << '\n';
		ans = min(ans,max(f1,f2));
		cout << ans << '\n';
		sb.erase(sb.find(it.second));
		s.erase(s.find(it));
		swap(it.first,it.second);
		s2.erase(s2.find(it));
		
	}
	return 0;
}
