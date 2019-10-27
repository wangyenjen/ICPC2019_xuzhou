#include<cstdio>
#include<iostream>
#include<cstdlib>
using namespace std;
const int MXN = (int)4e5 + 7;
const long long INFF = (long long)1e18;
int n, k;
long long xx[MXN], yy[MXN], h[MXN], dp[MXN];
pair<long long, int> stk[MXN]; 
bool check(pair<long long, int> l1, pair<long long, int> l2, pair<long long, int> l3) {
	if (l3.second == l2.second)
		return l2.first >= l3.first;
	long long v1 = (l2.first - l1.first) * (l1.second - l3.second);
	long long v2 = (l3.first - l1.first) * (l1.second - l2.second);
	return v1 >= v2;
}
void go(int l, int r) {
	if (l == r) {
		dp[l] = min(dp[l], dp[l-1] + yy[l]*k);
		return ;
	} 
	int mid = (l + r) >> 1;
	go(l, mid);
	for (int i = mid; i >= l; i--) {
		if (i == mid) h[i] = yy[i];
		else h[i] = max(h[i+1], yy[i]);
	}
	for (int i = mid+1; i <= r; i++) {
		if (i == mid+1) h[i] = yy[i];
		else h[i] = max(h[i-1], yy[i]);
	}

	// left side >= right side
	int ptr = l, ll = 0, rr = -1;
	for (int i = r; i >= mid+1; i--) {
		while (ptr != mid + 1 && h[ptr] >= h[i]) {
			pair<long long, int> line = {dp[ptr-1] + h[ptr]*(k - xx[ptr]), h[ptr]};
			while (rr - ll + 1 >= 2) {
				if (check(stk[rr-1], stk[rr], line)) rr--;
				else break ;
			}
			stk[++rr] = line;
			ptr++;
		}
		int lb = ll, rb = rr;
		while (lb + 9 <= rb) {
			int p1 = lb + (rb - lb) / 3;
			int p2 = rb - (rb - lb) / 3;
			long long v1 = stk[p1].first + stk[p1].second*xx[i];
			long long v2 = stk[p2].first + stk[p2].second*xx[i];
			dp[i] = min(dp[i], min(v1, v2));
			if (v1 >= v2) lb = p1 + 1;
			else rb = p2 - 1;
		}
		for (int j = lb; j <= rb; j++)
			dp[i] = min(dp[i], stk[j].first + stk[j].second*xx[i]);
	}	
	// left side < right side
	ptr = mid, ll = n+1, rr = n;
	for (int i = mid+1; i <= r; i++) {
		while (ptr != l - 1 && h[ptr] <= h[i]) {
			pair<long long, int> line = {dp[ptr-1], -xx[ptr]};
			while (rr - ll + 1 >= 2) {
				if (check(line, stk[ll], stk[ll+1])) ll++;
				else break ;
			}
			stk[--ll] = line;
			ptr--;
		}
		while (rr - ll + 1 >= 2) {
			long long v1 = stk[ll].first + stk[ll].second*h[i];
			long long v2 = stk[ll+1].first + stk[ll+1].second*h[i];
			if (v1 >= v2) ll++;
			else break ;
		}
		if (rr >= ll) dp[i] = min(dp[i], stk[ll].first + h[i]*(stk[ll].second + xx[i] + k));
	}

	go(mid+1, r);
}
int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld", xx + i, yy + i);
		dp[i] = INFF;
	}
	go(1, n);
	printf("%lld\n", dp[n]);
	return 0;
}
