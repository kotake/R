#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char const* argv[])
{
	int     max1 = 4;
	int     max2 = 4;
	vector< vector<int> > v (max1, vector<int>(max2) );//()で書くと初期要素数を指定できる

	for (int i = 0; i < max1; ++i) {
		for (int j = 0; j < max2; ++j) {
			v[i][j] = i * j;
		}
	}
	for (auto v1: v) {
		for(auto v2: v1) {
			cout << v2 << " ";
		}
		cout << endl;
	}
	return 0;
}
