#include <iostream>
#include "statistics.h"

using namespace std;
using namespace alglib;

int main()
{
	// ALGLIBを用いた相関係数の算出

	real_2d_array x = "[0,1,2,3][3]";
	real_2d_array y = "[0,1,2,4][4]";
	double v;

	cout.precision(8);

	// 共分散
	v = cov2(x, y);
	cout << "共分散: " << double(v) << endl;

	// Pearsonの相関係数
	v = pearsoncorr2(x, y);
	cout << "Pearsonの相関係数: " << double(v) << endl;

	// Spearmanの相関係数
	v = spearmancorr2(x, y);
	cout << "Spearmanの相関係数: " << double(v) << endl;

	return 0;
}
