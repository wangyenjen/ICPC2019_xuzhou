#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
#define REP(i,j,k)     for(int i = j ; i < k ; ++i)
#define RREP(i,j,k)    for(int i = j ; i >=k ; --i)
#define A    first
#define B    second
#define mp   make_pair
#define pb   emplace_back
#define PII pair<int , int>
#define MEM(i,j)   memset(i , j , sizeof i)
#define ALL(i)     i.begin() , i.end()
#define DBGG(i,j)     cout << i << " " << j << endl
#define DB4(i,j,k,l)  cout << i << " " << j << " " << k << " " << l << endl
#define IOS cin.tie() , cout.sync_with_stdio(0)
#define endl "\n"
///------------------------------------------------------------
#define MAX 100900
#define INF 0x3f3f3f3f
 
int fir[MAX] , trs[MAX] , dep[MAX] , idpo = 0;

int n , m , N , x[MAX] , e[MAX][2] , q[MAX][2];

int ql[MAX] , qr[MAX];

int sol[MAX] , use[MAX] , ans[MAX];

int cnt[MAX] , ccc[MAX] , answer = 0;

vector<int> v[MAX];

void DFS(int now , int fa , int deep){
    dep[now] = deep;
	fir[now] = idpo + 1;
	for(auto to : v[now]) if(to != fa){
		trs[++idpo] = to;
		DFS(to , now , deep + 1);
		trs[++idpo] = to;
	}
}

int cmp(int a , int b){
	if(ql[a] / N != ql[b] / N) return ql[a] / N < ql[b] / N;
	if(ql[a] / N == ql[b] / N) return qr[a] / 1 < qr[b] / 1;
}
void update(int val , int add){
    if(cnt[val] != 0){
        answer -= ccc[cnt[val] * 2];
        answer -= ccc[cnt[val] / 2] * (cnt[val] % 2 == 0);
        ccc[cnt[val]] --;
    }
    cnt[val] += add;
    if(cnt[val] != 0){
        answer += ccc[cnt[val] * 2];
        answer += ccc[cnt[val] / 2] * (cnt[val] % 2 == 0);
        ccc[cnt[val]] ++;
    }
}
void modify(int id){
	if(use[id] == 0) return use[id] = 1 , update(x[id] , 1) , void();
	if(use[id] == 1) return use[id] = 0 , update(x[id] ,-1) , void();
}
void solve(){
    DFS(1 , 0 , 1);
    REP(i , 2 , n + 1){
        if(dep[e[i][0]] > dep[e[i][1]]) x[e[i][0]] = e[i][2];
        if(dep[e[i][0]] < dep[e[i][1]]) x[e[i][1]] = e[i][2];
    }
	REP(i , 1 , m + 1) sol[i] = i;
	REP(i , 1 , m + 1){
		ql[i] = min(fir[q[i][0]] , fir[q[i][1]]);
		qr[i] = max(fir[q[i][0]] , fir[q[i][1]]) - 1;
	}
	sort(sol + 1 , sol + 1 + m , cmp);
	int l = 1 , r = 0;
	REP(i , 1 , m + 1){
		int id = sol[i];
		while(r < qr[id]) modify(trs[++ r]);
		while(qr[id] < r) modify(trs[r --]);
		while(l < ql[id]) modify(trs[l ++]);
		while(ql[id] < l) modify(trs[-- l]);
		ans[id] = answer;
	}
}

int32_t main(){
    IOS;
	cin >> n >> m;
	N = sqrt(n) + 1;
    
	REP(i , 2 , n + 1){
        cin >> e[i][0] >> e[i][1] >> e[i][2];
        v[e[i][0]].pb(e[i][1]);
        v[e[i][1]].pb(e[i][0]);
	}
 
	REP(i , 1 , m + 1) cin >> q[i][0] >> q[i][1];
	
    solve();
	
    REP(i , 1 , m + 1) cout << ans[i] << endl;
    return 0;
}  
