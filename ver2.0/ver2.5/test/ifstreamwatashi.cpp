#include<iostream>
#include<fstream>
#include<string>
using namespace std;

ifstream* fp_inc(ifstream &fp){
	string ss;
	fp >> ss;
	cout << ss << endl;
	return &fp;
}

int main(){
	ifstream ifs("ifstream_input.txt");
	//string s;
	if(ifs.fail())
		cout <<"soppai"<<endl;

	for(int i=0;!ifs.eof();i++){
		//ifs >> s;
		//cout << s << endl;
		 fp_inc(ifs);
	}

	return 0;
}
