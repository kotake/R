#include <iostream>
using namespace std;
bool csv_read(double *c){
	//c = new double[3];
	c[0] = 1;
	c[1] = 2;
	c[2] = 3;

	for(int i=0;i<3;i++){
		cout << c[i]<<endl;
	}
	return true;
}

void wa(int n, int *a, int *b, int *c)
{
	int i1;

	for (i1 = 0; i1 < n; i1++)
		c[i1] = a[i1] + b[i1];
}
