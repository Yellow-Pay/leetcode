#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

// optiver scholarship
// 2D grid random walk
// every step your can choose 4 directions to walk 1 unit or stop
// once stop, then never walk again


//#define DEBUG
/*
 *  * Complete the function below.
 *   */
float ExpectedCrabWalk(int numsteps) {
	// pos(t,x,y)=0.2*(pos(t-1,x,y)+pos(t-1,x+1,y)+pos(t-1,x-1,y)+pos(t-1,x,y-1)+pos(t-1,x,y+1))
	// pos(t,x,y)=0 if x+y>t
	// only consider x>=0 and y>=0
	if (numsteps > 100) return 1.47513;
	vector<vector<vector<float>>> cube;
	vector<vector<float>> matrix;
	vector<float> line;
	vector<vector<float>> odd_matrix; // need to subtract when step is odd
	vector<vector<float>> even_matrix;
	line.resize(2 * numsteps+1,0);
	matrix.resize(2 * numsteps+1,line);
	odd_matrix.resize(2 * numsteps+1, line);
	even_matrix.resize(2 *numsteps+1, line);
	cube.resize(numsteps+1,matrix);
	float res = 0;
	cube[0][numsteps][numsteps] = 1;
	even_matrix[numsteps][numsteps] = 1; // non-stop, need to subtract
	for (int t = 1; t <= numsteps; ++t) {
		for (int x = 0; x <= 2* numsteps; ++x) {
			for (int y = 0; y <= 2 * numsteps; ++y) {
				if (t < abs(x - numsteps) + abs(y - numsteps)) continue;
				if ((t - x - y) % 2) { // (1, 0, 0) or (2, 1, 0)
					cube[t][x][y] = cube[t-1][x][y] * 0.2;
				} else { // active
					if (x > 0)
					      cube[t][x][y] += cube[t-1][x-1][y];
					if (x < 2 * numsteps)
					      cube[t][x][y] += cube[t-1][x+1][y];
					if (y > 0)
					      cube[t][x][y] += cube[t-1][x][y-1];
					if (y < 2 * numsteps)
					      cube[t][x][y] += cube[t-1][x][y+1];
					cube[t][x][y] *= 0.2;
				}
			}
		}
		for (int x = 0; x <= 2 * numsteps; ++x) {
			for (int y = 0; y <= 2 * numsteps; ++y) {
				if ((t-x-y) % 2) {
					cube[t-1][x][y] = 0;
				}
			}
		}
	}
//	double sum = 0;
	for (int t = 0; t <= numsteps; ++t) {
		for (int x = 0; x <= 2 * numsteps; ++x) {
			for (int y = 0; y <= 2 * numsteps; ++y) {
#ifdef DEBUG
				if (cube[t][x][y])
					cout << "Weight = (" << t << "," << x-numsteps << "," << y-numsteps << ") = " << cube[t][x][y] << endl;
#endif
//				sum += cube[t][x][y];
				res += cube[t][x][y] * (sqrt((x-numsteps)*(x-numsteps)+(y-numsteps)*(y-numsteps)));
			}
		}
	}
//	cout << "sum = " << sum << '\n';
	return res;
}
int main () {
	for (int i = 0; i < 1000; i++) {
		cout << "res(" << i << ") = " << ExpectedCrabWalk(i) << '\t';
		if (i % 5 == 4) {
			cout << endl;
		}
	}
	return 0;
}

