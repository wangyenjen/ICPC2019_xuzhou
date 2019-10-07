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

const int maxn = 100000;
int pos = 0;
fstream file;

void P(vector<int> p, vector<int> c, vector<PII> q){
    string in = "../inputs/", out = "../outputs/";
    in += '0' + pos / 10, in += '0' + pos % 10;
    out += '0' + pos / 10, out += '0' + pos % 10, pos ++;
    out += ".out", in += ".in";
    
    file.open(in, ios::out);

	cout << "print test:" << (pos - 1) / 10 << (pos - 1) % 10 << endl;
    
    int n = p.size() + 1 , m = q.size();
    vector<int> trs;
    REP(i , 1 , n + 1) trs.pb(i);
    shuffle(trs.begin(), trs.end());
    
    assert(p.size() == c.size());
    file << n << " " << q.size() << endl;
    REP(i , 0 , p.size()) file << trs[p[i] - 1] << " " << trs[i + 2 - 1] << " " << c[i] << "\n";
    REP(i , 0 , q.size()) file << q[i].F << " " << q[i].S << "\n";
    file.close();
    
    int a;
    a = system(string("../validator/validator < " + in).c_str());
    a = system(string("../solution/ac < " + in + " > " + out).c_str());
}

vector<int> g[maxn + 10];

vector<int> gettree1(){
//    cout << "build tree in way1" << endl;
    vector<int> v;
    REP(i , 2 , maxn + 1){
        int val = rnd.next(1 , i - 1);
        REP(T , 0 , 50) val = min(val , rnd.next(1 , i - 1));
        v.pb(val);
    }
    return v;
}

vector<int> gettree2(){
//    cout << "build tree in way2" << endl;
    vector<int> v;
    REP(i , 2 , maxn + 1){
        int val = rnd.next(1 , i - 1);
        REP(T , 0 , 50) val = max(val , rnd.next(1 , i - 1));
        v.pb(val);
    }
    return v;
}

vector<int> gettree3(){
//    cout << "build tree in way3" << endl;
    vector<int> v;
    REP(i , 2 , maxn + 1)
        v.pb(i - 1);
    return v;
}

vector<int> gettree4(){
//    cout << "build tree in way3" << endl;
    vector<int> v;
    int pre = 1, cnt = 0;
    REP(i , 2 , maxn + 1){
        v.pb(pre) , cnt ++ , pre = i;
        if(cnt == 317) cnt = 0 , pre = 1;
    }
    return v;
}

vector<int> color1(vector<int> p){
//    cout << "color edge in way1" << endl;
    int n = p.size() + 1;
    vector<int> v;
    REP(i , 2 , n + 1) v.pb(rnd.next(1 , maxn));
    return v;
}

vector<int> color2(vector<int> p){
//    cout << "color edge in way2" << endl;
    int n = p.size() + 1;
    vector<int> v(n - 1) , t;
    assert(v.size() == n - 1);
    REP(i , 2 , n + 1) t.pb(i);
    shuffle(t.begin(), t.end());

    for(auto to : t){
        int cc = rnd.next(1 , maxn);
        v[to - 2] = cc;
        if(p[to - 2] != 1) v[p[to - 2] - 2] = cc;
    }
    return v;
}

vector<int> color3(vector<int> p){
//    cout << "color edge in way3" << endl;
    int n = p.size() + 1;
    vector<int> v;
    REP(i , 2 , n + 1) v.pb(rnd.next(1 , 317));
    return v;
}


vector<PII> query1(vector<int> p){
//    cout << "build query in way1" << endl;
    vector<PII> v;
    int n = p.size() + 1;
    REP(i , 1 , maxn + 1){
        v.pb(rnd.next(1 , n) , rnd.next(1 , n));
    }
    return v;
}

vector<PII> query2(vector<int> p){
//    cout << "build query in way2" << endl;
    int n = p.size() + 1;
    REP(i , 1 , n + 1) g[i].clear();
    REP(i , 0 , p.size()) g[p[i]].pb(i + 2) , g[i + 2].pb(p[i]);
    vector<PII> v;
    vector<int> d;
    REP(i , 1 , n + 1) if(g[i].size() == 1) d.pb(i);

    REP(i , 0 , d.size()) REP(j , i + 1 , d.size()){
        if(v.size() == maxn) break;
        v.pb(d[i] , d[j]);
    }
    while(v.size() != maxn)
        v.pb(rnd.next(1 , n) , rnd.next(1 , n));
    return v;
}



int32_t main(){
    
    int Tcnt = 4;
    int Ccnt = 3;
    int Qcnt = 2;
    
    REP(T , 1 , Tcnt + 1) REP(C , 1 , Ccnt + 1) REP(Q , 1 , Qcnt + 1){
        vector<int> p , c;
        vector<PII> q;
        
        if(T == 1) p = gettree1();
        if(T == 2) p = gettree2();
        if(T == 3) p = gettree3();
        if(T == 4) p = gettree4();

        if(C == 1) c = color1(p);
        if(C == 2) c = color2(p);
        if(C == 3) c = color3(p);

        if(Q == 1) q = query1(p);
        if(Q == 2) q = query2(p);

        P(p , c , q);
    }

    return 0;
}

