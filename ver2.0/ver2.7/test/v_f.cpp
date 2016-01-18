#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(void){
	vector<ofstream*> ofs;
	
	ofstream ofs1, ofs2, ofs3;
	ofs1.open("ofs/1.txt");
	ofs2.open("ofs/2.txt");
	ofs3.open("ofs/3.txt");

	ofs.push_back(&ofs1);
	ofs.push_back(&ofs2);
	ofs.push_back(&ofs3);
	
	cout << "ofs1のアドレス：" << ofs[0] << endl;	
	cout << "ポインタのアドレス："<< &ofs[0] << endl;	
	cout << "ofs1が指しているところ" << *ofs[0] << endl;	
	
	*ofs[0] << "test" << endl;

	for(int i=0;i<3;i++){
		(*ofs[i]).close();//or ofs[i]->close();
	}

	/////////////////////////////////////////
	ofstream fn[10];
	
	ofstream fn1,fn2,fn3;
	fn1.open("ofs/a.txt");
	fn2.open("ofs/b.txt");
	fn3.open("ofs/c.txt");
	
	fn[0] = fn1;
/*	fn[1] = fn2;
	fn[2] = fn3;

	fn[0] << "abc" << endl;

	fn1.close();
	fn2.close();
	fn3.close();

	for(int i=0;i<10;i++){
		fn[i].close();
	}
*/
	return 0;
}
