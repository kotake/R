#include<iostream>
using namespace std;
bool csv_read(double *c);
void wa(int n, int *a, int *b, int *c);

int main(){

	double * csv_data;
	csv_data = new double[3];
	if(csv_read(csv_data))	
		cout << "success"<<endl;
	for(int i=0;i<3;i++)
		cout << csv_data[i] <<endl;

	int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
	int i1, b[3];
	int *c;
	c = new int[3];

	wa(3, &a[0][0], &a[1][0], c);   /* １行目と２行目のベクトル和の計算 */
	for (i1 = 0; i1 < 3; i1++)
		cout<< c[i1]<<" ";
	cout << endl;

	return 0;

}
