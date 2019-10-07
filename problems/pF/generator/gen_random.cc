/// Author: Yen-Jen Wang
#include <bits/stdc++.h>

using namespace std;

void save_data(int N, vector<int> vs, int id) {
    char name_in[64], name_ans[64];
    sprintf(name_in, "./../data/random_%02d.in", id);
    sprintf(name_ans, "./../data/random_%02d.ans", id);

    FILE *fp = fopen(name_in, "w");
    fprintf(fp, "%d\n", N);
    for (int i = 0; i < N - 1; i++) {
      fprintf(fp, "%d%c", vs[i], " \n"[i == N - 2]);
    }
    fclose(fp);

    char order[128];
    sprintf(order, "./../sol < %s > %s", name_in, name_ans);
    system(order);
}

mt19937 meow(880301);

int my_rand(int l, int r) {
    return uniform_int_distribution<int>(l, r)(meow);
}

int main() {
    int data_id = 0;

    for (int times = 1; times <= 2; times++) {
        int N = my_rand(1, 1000000);
        vector<int> vs;

        int x = 1;
        for (int i = 1; i <= N; i++) {
            if (i != x)
                vs.push_back(i);
        }
        save_data(N, vs, ++data_id);

        vs.clear();
        x = N;
        for (int i = 1; i <= N; i++) {
            if (i != x)
                vs.push_back(i);
        }
        save_data(N, vs, ++data_id);

        vs.clear();
        x = my_rand(1, N);
        for (int i = 1; i <= N; i++) {
            if (i != x)
                vs.push_back(i);
        }
        save_data(N, vs, ++data_id);
    }

    for (int N = 1000000; N >= 1000000 - 3; N--) {
        vector<int> vs;

        int x = 1;
        for (int i = 1; i <= N; i++) {
            if (i != x)
                vs.push_back(i);
        }
        save_data(N, vs, ++data_id);

        vs.clear();
        x = N;
        for (int i = 1; i <= N; i++) {
            if (i != x)
                vs.push_back(i);
        }
        save_data(N, vs, ++data_id);

        vs.clear();
        x = my_rand(1, N);
        for (int i = 1; i <= N; i++) {
            if (i != x)
                vs.push_back(i);
        }
        save_data(N, vs, ++data_id);
    }

    return 0;
}

