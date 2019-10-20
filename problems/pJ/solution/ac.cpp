#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
#define REP(i,j,k)  for(int i = j ; i < k ; ++i)
#define RREP(i,j,k) for(int i = j ; i >=k ; --i)
#define F first
#define S second
#define mp make_pair
#define pb emplace_back
#define PII pair<int , int>
#define MEM(i,j) memset(i , j , sizeof i)
#define ALL(i)   i.begin() , i.end()
#define DBGG(i,j)     cout << i << " " << j << endl
#define DB4(i,j,k,l)  cout << i << " " << j << " " << k << " " << l << endl
#define IOS cin.tie(0) , cout.sync_with_stdio(0)
#define endl "\n"
///------------------------------------------------------------
#define MAX 1010
#define INF 0x3f3f3f3f

int n;

int u[MAX][MAX];
vector<int> v;

void DFS(int now){
    REP(i , 1 , n + 1) if(u[i][now] == 0 && i != now){
        u[i][now] = u[now][i] = 1;
        DFS(i);
        v.pb(now);
    }
}

int32_t main(){
	IOS;
    cin >> n;
    if(n % 2 == 0){
        for(int i = 2; i <= n; i += 2){
            vector<int> sol;
            int v1 = i - 1 , v2 = i;
            sol.pb(v2) , sol.pb(v1);
            for(int j = 1; j <= i - 2; j ++){
                sol.pb(j) , sol.pb(v2);
                swap(v1 , v2);
            }
            if(i != 2){
                for(int j = 0; j <= i - 2; j ++)
                    cout << sol[j] << (j + 2 == i ? "\n" : " ");
                //            cout << "---" << endl;
            }
            for(int j = i - 2; j < sol.size(); j ++)
                cout << sol[j] << (j + 1 == sol.size() ? "\n" : " ");
        }
    }
    if(n % 2 == 1){
        v.pb(1);
        DFS(1);
        int pos = 0;
        REP(i , 1 , n) {
            REP(j , pos , pos + i + 1) cout << v[j] << " \n"[j == pos + i];
            pos += i;
        }
//        for(auto to : v) cout << to << " " ; cout << endl;
    } 
    return 0;
}

