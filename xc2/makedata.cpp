#include<iostream>
#include<iomanip>
#include<random>

using namespace std;

int main(){

	int col_num = 10,row_num = 1000;
	char mozi = 'a';
		
	for(int i =0;i<col_num;i++,mozi++){
		cout << mozi;
		if(i!=col_num-1)cout << ",";
	}
	cout <<endl;

	random_device rnd;
	mt19937 mt(rnd());

	for(int i=0;i<row_num;i++){
		for(int j=0;j< col_num;j++){

			double rand = (mt()%100000)/1000.0;
			
			cout << setprecision(6) << rand;
			if(j!=col_num-1)cout << ", ";
		}
		cout << endl;
	}

}
