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

int pos = 0;
fstream file;

void P(int n){
    string in = "../inputs/", out = "../outputs/";
    in += '0' + pos / 10, in += '0' + pos % 10;
    out += '0' + pos / 10, out += '0' + pos % 10, pos ++;
    out += ".out", in += ".in";
    
    file.open(in, ios::out);

	cout << "start at test:" << pos << endl;
    
    file << n << endl;
    
    file.close();
    
    int ret;
    ret = system(string("../validator/validator < " + in).c_str());
    ret = system(string("../solution/ac < " + in + " > " + out).c_str());
}

void solve(){
    vector<int> v{
    2, 3, 4, 5, 6, 7, 8, 9, 209, 512, 678, 789, 991, 997, 998, 999, 1000
    };
    for(auto to : v) P(to);
}

int32_t main(){
    solve();
    return 0;
}

