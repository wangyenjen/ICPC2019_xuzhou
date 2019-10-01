#include "testlib.h"
using namespace std;

const int N = 300000;
const int INF = 1000000000;

int main(int argc, char **argv) {
	registerValidation(argc, argv);	
	int n = inf.readInt(1, N, "n");
	inf.readEoln();
	for (int i = 1; i <= n; i++) {
		inf.readInt(1, INF, "a");
		inf.readSpace();
		inf.readInt(1, INF, "b");
		inf.readEoln();
	}
	inf.readEof();
	return 0;
}
