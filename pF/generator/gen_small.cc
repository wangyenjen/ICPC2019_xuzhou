/// Author: Yen-Jen Wang
#include <bits/stdc++.h>

using namespace std;

void save_data(int N, vector<int> vs, int id) {
    char name_in[32], name_ans[32];
    sprintf(name_in, "./../data/small_%02d.in", id);
    sprintf(name_ans, "./../data/small_%02d.ans", id);

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

    for (int N = 1; N <= 7; N++) {
        vector<int> vs;
        for (int i = 1; i <= N; i++) {
            vs.clear();

            for (int j = 1; j <= N; j++) {
              if (j != i)
                vs.push_back(j);
            }

            shuffle(vs.begin(), vs.end(), meow);

            save_data(N, vs, ++data_id);
        }
    }

    return 0;
}

