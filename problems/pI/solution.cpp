#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
const int MXN = 3e5 + 7;
int a[MXN], b[MXN];
struct Item1 {
	int v1, v2, id;
	Item1(){};
	Item1(int _v1, int _v2, int _id) {
		v1 = _v1, v2 = _v2, id = _id;
	}
	bool operator <(const Item1 &p1) const {
		if (v1 != p1.v1) return v1 > p1.v1;
		else if (v2 != p1.v2) return v2 < p1.v2;
		else return id < p1.id;
	} 
};
struct Item2 {
	int v1, v2, id;
	Item2(){};
	Item2(int _v1, int _v2, int _id) {
		v1 = _v1, v2 = _v2, id = _id;
	}
	bool operator <(const Item2 &p1) const {
		if (v2 != p1.v2) return v2 > p1.v2;
		else if (v1 != p1.v1) return v1 > p1.v1;
		else return id < p1.id;
	} 
};
int ans[MXN];
int main(void) {
	int n; scanf("%d", &n);
	set<Item1> st1;
	set<Item2> st2;
	set<pair<int, int>> st;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", a + i, b + i);
		st1.insert(Item1(a[i], b[i], i));
		st2.insert(Item2(a[i], b[i], i));
		st.insert({b[i], i});
	}
	for (int i = 0; i <= n - 2; i++) {
		pair<pair<int, int>, int> p1;
		p1.first.first = st1.begin()->v1;
		p1.first.second = st1.begin()->v2;
		p1.second = st1.begin()->id;

		pair<pair<int, int>, int> p2;
		p2.first.first = st2.begin()->v1;
		p2.first.second = st2.begin()->v2;
		p2.second = st2.begin()->id;

		int v1 = p1.first.first - (--st.end())->first;
		if ((--st.end())->second == p1.second) 
			v1 = p1.first.first - (--(--st.end()))->first;
		int v2 = p2.first.first - (--st.end())->first;
		if ((--st.end())->second == p2.second) 
			v2 = p2.first.first - (--(--st.end()))->first;
		if (v1 >= v2) {
			ans[i] = v1;
			st1.erase(Item1(p1.first.first, p1.first.second, p1.second));
			st2.erase(Item2(p1.first.first, p1.first.second, p1.second));
			st.erase({p1.first.second, p1.second});
		} else {
			ans[i] = v2;
			st1.erase(Item1(p2.first.first, p2.first.second, p2.second));
			st2.erase(Item2(p2.first.first, p2.first.second, p2.second));
			st.erase({p2.first.second, p2.second});
		}
		if (i) ans[i] = min(ans[i], ans[i-1]);
	}
	for (int i = 0; i <= n - 2; i++)
		printf("%d\n", ans[i]);
	return 0;
}

