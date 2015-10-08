#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> Split(string &src, string key);
bool readCSV(string filename, int* p);

int main(void){
	int data[256];//ファイルから読み込んだ数値を入れる配列

	readCSV("test.csv", data);//ファイルから読み込み

	//最初の10個を表示させてみる
	for(int i = 0; i < 10; ++i) {
		cout << data[i] << endl;
	}
}

bool readCSV(string filename, int* p) {
	fstream file;
	string str;

	file.open(filename.c_str(), ios::in);
	if(! file.is_open()) {
		return false;
	}

	while(getline(file, str)) {
		vector<string> str_line = Split(str, (string)",");
		int size = str_line.size();

		for(int i = 0; i < size; ++i) {
			stringstream sstr;
			sstr << str_line[i];
			sstr >> p[i];
		}
		p += size;
	}
	file.close();
	return true;
}

vector<string> Split(string &src, string key) {

	string str = src;
	vector<string> str_line;
	int str_len = str.length();
	int key_len = key.length();

	int index = 0;
	while(index < str_len) {
		int oldindex = index;
		index = str.find(key, index);
		index = (index == string::npos ? str_len : index);
		string tmp = str.substr(oldindex, index - oldindex);
		str_line.push_back(tmp);
		index += key_len;
	}
	return str_line;
}
