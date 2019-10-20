#include <bits/stdc++.h>
using namespace std;
#define REP(i , j , k) for(int i = j; i < k; i ++)

#define MAX 300900
int n , k , p[MAX];
string s;

int main(){

    cin >> n >> k >> s;
    REP(i , 2 , n + 1) cin >> p[i];
    REP(i , 1 , k + 1){
        int now , len;
        cin >> now >> len;
        string ss;
        REP(j , 0 , len) ss += s[now - 1], now = p[now];
//        cout << "ss = " << ss << endl;
        int ans = 0;
        REP(ii , 1 , n + 1){
            string f;
            int tmp = ii;
            REP(j , 0 , len) if(tmp != 0) f += s[tmp - 1] , tmp = p[tmp];
            if(f == ss) ans ++;
        }
        cout << ans << endl;
    }
    
    return 0;
}
