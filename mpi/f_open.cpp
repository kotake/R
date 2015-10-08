#include<iostream>
#include<fstream>
#include<string>

#define MAX_COL 10
//#define MAX_LINE 100

using namespace std;

int main()
{
	ifstream ifs;
	char buf[256];

	ifs.open("test.csv");
	if(!ifs){
		cout <<"error"<<endl;
		return 1;	
	}

	int linenum = 0;

	//列数カウント

	//行数カウント
	while(ifs.getline(buf,sizeof(buf))){
		linenum++;
	}

	//ファイル末尾というフラグをクリア
	ifs.clear();
	//ファイルの先頭に戻る
	ifs.seekg(0, ios::beg);

	string *rabel,*csvdata;
	rabel = new string[MAX_COL];
	csvdata = new string[(MAX_COL-1)*linenum];

	for(int i=0;i<linenum;i++)
	{

		while('\n' != ifs.getline(buf,sizeof(buf),','))
		{
			csvdata[i] = buf;
			cout << buf;
		}
	}

	ifs.close();

	cout << endl << "結果" <<endl;
	for(int i=0;i<linenum;i++)
	{
		cout << csvdata[i];
	}

	return 0;
}
