#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;
int main(){

	ifstream ifs("../all/association/foo.txt");
	if(!ifs)
		cout<<"sippai"<<endl;

	string s,tmp;
	int col=1;
	
	for(int i=0;!ifs.eof();){
		ifs >> s;

		//もし末文字が,なら
		while(s[s.size()-1] == ','){
			tmp = s;
			ifs >> s;
			s = tmp + s;
		};

		//string => int
		stringstream ss;
		int si;
		ss << s;
		ss >> si;

		//行頭なら改行しておく
		if(si==col){
			cout << endl;
			col++;
		};
		
		cout << s << " ";
	}
	return 0;
}
