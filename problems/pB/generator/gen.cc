/// Author: Yen-Jen Wang
#include "testlib.h"

#include <bits/stdc++.h>

using namespace std;

int RandInt(int lower_bound, int upper_bound) {
  return rnd.next(lower_bound, upper_bound);
}

string IntToString(int x) {
	string res = "";
  if (x == 0) {
    res = "0";
  } else {
    while (x) {
      res += (char)(x % 10 + '0');
      x /= 10;
    }
  }
  reverse(res.begin(), res.end());
  return res;
}

void SaveData(const int& k,
    const int& id,
    const vector<int>& vs) {
  const string& name_in = "./../data/" + IntToString(k) + "-" + IntToString(id) + ".in";
  const string& name_ans = "./../data/" + IntToString(k) + "-" + IntToString(id) + ".ans";
  FILE *fp = fopen(name_in.c_str(), "w");
  fprintf(fp,"%d\n", (int)vs.size());
  for (int i = 0; i < (int)vs.size(); i++) {
    fprintf(fp, "%d %d\n", vs[i], k);
  }
  fclose(fp);

  char order[512];
  sprintf(order, "./../solutions/sol < %s > %s", name_in.c_str(), name_ans.c_str());
  system(order);
}

void Build() {
  for (int k = 1; k <= 3; k++) {
    for (int id = 1; id <= 10; id++) {
      vector<int> vs;
      for (int i = 100000 * (id - 1) + 1; i <= 100000 * id; i++) {
        vs.push_back(i);
      }
      SaveData(k, id, vs);
    }
  }
}

int main(int argc, char** argv) {
  registerGen(argc, argv, 1);
  Build();
  return 0;
}
