#include "./../include/testlib.h"
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

int u[MAX][MAX];

int32_t main(int argc, char *argv[]){
    IOS;
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(), in , ok = 1;
    inf.readEoln();
    inf.readEof();

    REP(i , 1 , n){
        vector<int> v;
        REP(j , 1 , i + 2) v.pb(ouf.readInt(1, n)), ans.readInt();
        ouf.readEoln();
        ans.readEoln();
        REP(j , 1 , v.size()){
            int v1 = v[j - 1] , v2 = v[j];
            if(v1 == v2) quitf(_wa, "It's not an edge.");
            if(u[v1][v2] == 1) quitf(_wa, "Use same edge many times.");
            u[v1][v2] = u[v2][v1] = 1;
        }
    }
    ouf.readEof(), ans.readEof();
    quitf(_ok, "AC");
    return 0;
}

