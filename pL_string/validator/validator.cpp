#include "./../../include/testlib.h"
#include <bits/stdc++.h>
using namespace std;

#define MAX 300005
vector<int> v[MAX];
int dep[MAX];
int DFS(int now , int deep){
    dep[now] = deep;
    for(auto to : v[now])
        DFS(to , deep + 1);
}

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    const int maxn = 300000;
    int n = inf.readInt(1, maxn, "n");
    inf.readSpace();
    int k = inf.readInt(1, maxn, "n");
    inf.readEoln();
    for(int i = 1; i <= n; i ++){
        int c = inf.readChar();
        assert(c >= 'A' && c <= 'Z');
    }
    inf.readEoln();
    for(int i = 2; i <= n; i ++){
        v[inf.readInt(1, i - 1, "p_i")].push_back(i);
        if(i != n) inf.readSpace();
    }
    inf.readEoln();
    DFS(1 , 1);
    for(int i = 1; i <= k; i ++){
        int v1 = inf.readInt(1 , n , "q_1");
        inf.readSpace();
        int v2 = inf.readInt(1 , n , "q_2");
        assert(v2 <= dep[v1]);
        inf.readEoln();
    }

    inf.readEof();
}
