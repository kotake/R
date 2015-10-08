#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

int main()
{
	ifstream fin;
	char ch;

	string *rabel;
	rabel = new string[100];

	double *csv_data;
	csv_data = new double[1000];

	fin.open("iris.csv");

	char buf;

	string line;
	unsigned int index = 0,row_num=0,col_num=0;

	//1行目をrabelとして読み込む
	getline(fin,line);
	stringstream s1;
	s1<<line;
	string value;
	while(getline(s1,value,','))
	{	
		if(value == "\0")//セルが空の場合0を入れる
		{ 
			value = "0";
		}

		rabel[index]=value;
		index++;
	}	
	col_num = index;
	cout<<"col_num:"<<col_num<<endl;;
	index = 0;

	//2行目から読み込む
	while(getline(fin, line)){
		stringstream s2;
		s2 << line;
		//さっき読み込んだ行からカンマまでの読み込みを繰り返す
		while(getline(s2, value, ',')){
			//cout<<" value:"<<value<<" gcount:"<< ss.peek();
			if(value == "\0")//セルが空の場合0を入れる
			{ 
				value = "0";
			}
			stringstream ss(value);
			ss >> csv_data[index];
			//csv_data[index] = stod(value);
			
			index++;
		}
		row_num++;
	}

	if(index%row_num!=0)
	{
		cout<<"正しいcsvファイルではありません。縦横のサイズを合わせてください。"<<endl;
		//return -1;
	}
	if(col_num!=index/row_num) cout<<"なにかがおかしい"<<endl;
	cout << "index:"<<index<<" row_num:"<< row_num << " col_num:"<< index/row_num <<endl;

	for(int i=0;i<col_num;i++){
		cout << "rabel["<<i<<"]address:"<<&rabel[i]<<" 中身:"<<rabel[i] << endl;
	}

	for(int i=0;i<index;i++){
		cout << "csv_data["<<i<<"]address:"<<&csv_data[i]<<" 中身:"<<csv_data[i] << endl;
	}

	fin.close();

	delete [] csv_data;
	return 0;
}
