#include "testlib.h"
using namespace std;

const int N = 200000;
const int INF = 1000000;

int main(int argc, char **argv) {
	registerValidation(argc, argv);	
	int n = inf.readInt(1, N, "n");
	inf.readSpace();
	inf.readInt(1, INF, "k");
	inf.readEoln();
	int pre = -INF - 1;
	for (int i = 1; i <= n; i++) {
		int x = inf.readInt(pre+1, INF, "x");
		inf.readSpace();
		inf.readInt(1, INF, "y");
		inf.readEoln();
		pre = x;
	}
	inf.readEof();
	return 0;
}
