#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

int main()
{
	ifstream fin;
	char ch;

	string *csv_data;
	csv_data = new string[100];

	fin.open("test.csv");

	int col_num=0;
	char buf;
	
	string line;
	unsigned int index = 0,row_num=0;
	
	//1行読み込む
	while(getline(fin, line)){
		stringstream ss;
		ss << line;
		string value;
		//さっき読み込んだ行からカンマまでの読み込みを繰り返す
		while(getline(ss, value, ',')){
			//cout<<" value:"<<value<<" gcount:"<< ss.peek();
			if(value == "\0")//セルが空の場合0を入れる
			{ 
				value = "0";
			}
			csv_data[index] = value;
			index++;
		}
		
		row_num++;
	}

	if(index%row_num!=0)
	{
		cout<<"正しいcsvファイルではありません。縦横のサイズを合わせてください。"<<endl;
		//return -1;
	}
	cout << "index:"<<index<<" row_num:"<< row_num << " col_num:"<< index/row_num <<endl;
	for(int i=0;i<30;i++){
		cout << "csv_data["<<i<<"]address:"<<&csv_data[i]<<" 中身:"<<csv_data[i] << endl;
	}

	fin.close();

	delete [] csv_data;
	return 0;
}
