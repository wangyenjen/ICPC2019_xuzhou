#include "./../../include/testlib.h"
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
#define MAX 
#define INF 0x3f3f3f3f

const int maxn = 300000;
int pos = 0;
fstream file;

void P(vector<int> p , vector<int> x , vector<PII> q){
    string in = "../inputs/", out = "../outputs/";
    in += '0' + pos / 10, in += '0' + pos % 10;
    out += '0' + pos / 10, out += '0' + pos % 10, pos ++;
    out += ".out", in += ".in";
    
    file.open(in, ios::out);

	cout << "print test:" << (pos - 1) / 10 << (pos - 1) % 10 << endl;
    
    file << x.size() << " " << q.size() << endl;
    REP(i , 0 , x.size()) file << char(x[i] + 'A'); file << "\n";
    REP(i , 0 , p.size()) file << p[i] << (i + 1 == p.size())[" \n"];
    REP(i , 0 , q.size()) file << q[i].F << " " << q[i].S << "\n";
    
    file.close();
    
    int a;
    a = system(string("../validator/validator < " + in).c_str());
    a = system(string("../solution/ac < " + in + " > " + out).c_str());
}

vector<int> g[maxn + 10];
int dep[maxn + 10] , dtc[maxn + 10];

void DFS(int now , int deep){
    dep[now] = deep;
    for(auto to : g[now])
        DFS(to , deep + 1);
}
void getdep(vector<int> p){
    int n = p.size() + 1;
    REP(i , 1 , n + 1) g[i].clear();
    REP(i , 2 , n + 1) g[p[i - 2]].pb(i);
    DFS(1 , 1);
}

vector<int> gettree1(){
    cout << "build tree in way1" << endl;
    vector<int> v;
    REP(i , 2 , maxn + 1){
        int val = rnd.next(1 , i - 1);
        REP(T , 0 , 50) val = min(val , rnd.next(1 , i - 1));
        v.pb(val);
    }
    return v;
}

vector<int> gettree2(){
    cout << "build tree in way2" << endl;
    vector<int> v;
    REP(i , 2 , maxn + 1){
        int val = rnd.next(1 , i - 1);
        REP(T , 0 , 50) val = max(val , rnd.next(1 , i - 1));
        v.pb(val);
    }
    return v;
}

vector<int> gettree3(){
    cout << "build tree in way3" << endl;
    vector<int> v; 
    REP(i , 2 , maxn + 1)
        v.pb(rnd.next(1 , i - 1));
    return v;
}

vector<int> gettree4(){
    cout << "build tree in way4" << endl;
    vector<int> v;
    REP(i , 2 , maxn + 1)
        v.pb(i - 1);
    return v;
}

vector<int> color1(vector<int> p){
    int n = p.size() + 1;
    vector<int> v;
    REP(i , 1 , n + 1) v.pb(10);
    return v;
}

vector<int> color2(vector<int> p){
    int n = p.size() + 1;
    vector<int> v;
    REP(i , 1 , n + 1) v.pb(rnd.next(0 , 1) + 15);
    return v;
}

vector<int> color3(vector<int> p){
    int n = p.size() + 1;
    vector<int> v;
    getdep(p);
    REP(i , 1 , n + 1) dtc[i] = rnd.next(0 , 25);
    REP(i , 1 , n + 1) v.pb(dtc[dep[i]]);
    return v;
}


int32_t main(){
    REP(t , 1 , 4 + 1) REP(c , 1 , 3 + 1){
        vector<int> p , x;
        if(t == 1) p = gettree1();
        if(t == 2) p = gettree2();
        if(t == 3) p = gettree3();
        if(t == 4) p = gettree4();
        
        if(c == 1) x = color1(p);
        if(c == 2) x = color2(p);
        if(c == 3) x = color3(p);
        
        getdep(p);
        int n = x.size();
        vector<PII> q;
        REP(i , 1 , maxn + 1){
            int idx = rnd.next(1 , n);
            if(i < maxn / 10 * 1)
                q.pb(idx , 1);
            else if(i < maxn / 10 * 3)
                q.pb(idx , dep[idx]);
            else if(i < maxn / 10 * 3)
                q.pb(idx , rnd.next(1 , dep[idx]));
            else {
                int T = rnd.next(1 , 10) , len = dep[idx];
                while(T --) len = min(len , rnd.next(1 , dep[idx]));
                q.pb(idx , len);
            }
        }

        P(p , x , q);
    }
    return 0;
}

