/*input
6 3
ABABBA
1 1 3 3 4
1 1
6 4
5 2
*/
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
#define MAX 300900
#define INF 0x3f3f3f3f


const int nn = 20;

string s;
int n, k, sp[MAX][nn], hs[MAX][nn];

int c[MAX] , y[MAX] , z[MAX] , sa[MAX] , rk[MAX] , lcp[MAX] , dep[MAX];

void getsa(){
    REP(j , 2 , nn) REP(i , 1 , n + 1)
        sp[i][j] = sp[sp[i][j - 1]][j - 1];

    int m = 'Z';
    REP(i , 1 , n + 1) c[hs[i][0]] ++;
    REP(i , 1 , m + 1) c[i] += c[i - 1];
    REP(i , 1 , n + 1) sa[c[hs[i][0]] --] = i;
    
//    cout << "now d = " << 0 << endl;
//    REP(i , 1 , n + 1) cout << sa[i] << " " ; cout << endl;

    REP(d , 1 , nn){
        REP(i , 1 , m + 1) c[i] = 0;
        REP(i , 1 , n + 1) c[hs[sp[i][d]][d - 1]] ++;
        REP(i , 1 , m + 1) c[i] += c[i - 1];
        REP(i , 1 , n + 1) y[c[hs[sp[i][d]][d - 1]] --] = i;
        
        REP(i , 1 , m + 1) c[i] = 0;
        REP(i , 1 , n + 1) c[hs[i][d - 1]] ++;
        REP(i , 1 , m + 1) c[i] += c[i - 1];
        RREP(i , n , 1) sa[c[hs[y[i]][d - 1]] --] = y[i];

        hs[sa[1]][d] = 1;
        REP(i , 2 , n + 1){
            int v1 = sa[i - 1] , v2 = sa[i] , v1p = sp[v1][d] , v2p = sp[v2][d];
//            cout << "i = " << i << " " << v1 << " " << v2 << " " << v1p << " " << v2p << endl;
            hs[v2][d] = hs[v1][d] + (hs[v1][d - 1] != hs[v2][d - 1] || hs[v1p][d - 1] != hs[v2p][d - 1]);
        }
        m = hs[sa[n]][d];

//        cout << "now d = " << d << endl;
//        REP(i , 1 , n + 1) cout << sa[i] << " "; cout << endl;
//        REP(i , 1 , n + 1) cout << hs[sa[i]][d] << " " ; cout << endl;
    }            
}
void getlcp(){
    REP(i , 1 , n + 1) rk[sa[i]] = i;
    REP(i , 2 , n + 1){
        int v1 = sa[i - 1] , v2 = sa[i];
//        cout << v1 << " " << v2 << endl;
        RREP(j , nn - 2 , 0){
            if(hs[v1][j] == hs[v2][j]){
                v1 = sp[v1][j + 1];
                v2 = sp[v2][j + 1];
                lcp[i] += (1 << j);
            }
        }
//        cout << "i = " << i << " " << v1 << " " << v2 << endl;
        lcp[i] = min(lcp[i] , min(dep[sa[i - 1]] , dep[sa[i]]) + 1);
    }
    
    REP(i , 1 , n + 1) z[i] = z[(i - 1) / 2] + 1;
    
    REP(i , 1 , n + 1) sp[i][0] = dep[rk[i]];
    REP(i , 1 , n + 1) sp[i][1] = lcp[i + 1];
    REP(j , 2 , nn) REP(i , 1 , n + 1) 
        if(i + (1 << (j - 2)) <= n) 
            sp[i][j] = min(sp[i][j - 1] , sp[i + (1 << (j - 2))][j - 1]);
}

inline int query(int l , int r){
    if(l == r) return sp[l][0];
    int len = z[r - l + 1];
//    cout << "ql = " << l << " " << "qr = " << r << " " << l << "-" << l + (1 << (len - 1));
//    cout << " " << r - (1 << (len - 1)) << "-" << r << endl;
//    cout << "ans = " << min(sp[l][len] , sp[r - (1 << (len - 1))][len]) << endl;
    return min(sp[l][len] , sp[r - (1 << (len - 1))][len]);
}

int32_t main(){
    IOS;
    cin >> n >> k >> s;
    REP(i , 2 , n + 1) cin >> sp[i][1];
    REP(i , 2 , n + 1) dep[i] = dep[sp[i][1]] + 1;
    
    REP(i , 1 , n + 1) hs[i][0] = s[i - 1];
    REP(i , 1 , n + 1) sp[i][0] = i;
    
    getsa();
    getlcp();

//	  cout << "n = " << n << endl;
//    REP(i , 1 , n + 1) cout << lcp[i] << " " ;cout << endl;
//    REP(i , 1 , n + 1) cout << sa[i] << " "; cout << endl;
//    REP(i , 1 , n + 1) cout << rk[i] << " "; cout << endl;

    REP(t , 1 , k + 1){
        int now , len , vl , vr;
        cin >> now >> len;
        now = vl = vr = rk[now];
//        cout << "now = " << now << endl; 
        RREP(i , nn , 0){
            int to = vl - (1 << i);
            if(to >= 1 && query(to , now) >= len) vl = to;
        }
        RREP(i , nn , 0){
            int to = vr + (1 << i);
            if(to <= n && query(now , to) >= len) vr = to;
        }
        cout << vr - vl + 1 << "\n";
    }

    return 0;
}

