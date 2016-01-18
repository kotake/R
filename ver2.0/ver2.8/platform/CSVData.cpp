#include "CSVData.hpp"

//template <class T>
void CSVData::save_to(const string filename){

}

//template <class T>
void CSVData::load_from(const string filename){

	//CSVData object;

	ifstream fin, row_num_check;
	fin.open(filename);

	if(!fin){
		cout << "ファイルがオープンできません。"<<endl;
	}
	row_num_check.open(filename);

	//char buf;

	string line,temp;

	col_num = 0;
	row_num = 0;
	index = 0;

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

		rabel.push_back(value);
		col_num++;
	}	

	cout<<"col_num:"<< col_num <<endl;;

	//入力ファイルの行数確認
	while(getline(row_num_check, temp)){
		row_num++;
	}
	row_num = row_num - 1;

	//2行目から読み込む
	while(getline(fin, line)){
		stringstream s2;
		s2 << line;
		double d;
		//さっき読み込んだ行からカンマまでの読み込みを繰り返す
		while(getline(s2, value, ',')){
			if(value == "\0")//セルが空の場合0を入れる
			{ 
				value = "0";
			}
			stringstream ss(value);
			ss >> d;
			csv_data.push_back(d);

			index++;
		}
	}

	if(index % row_num!=0)
	{
		cout<<"正しいcsvファイルではありません。縦横のサイズを合わせてください。"<<endl;
	}

	if(col_num != index / row_num) cout<<"なにかがおかしい"<<endl;
	cout << "index:"<< index<<" row_num:"<< row_num << " col_num:"<< index / row_num << endl;
}
