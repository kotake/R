#include "head.hpp"

int conb(int n, int r)
{
	if(n < 0 || r < 0 || n < r) return 0;
	if(!r) return 1;
	return conb(n - 1, r - 1) + conb(n - 1, r);
}

//収束判定(各点が属するクラスタが変化しないかどうか)
bool isEqual(vector<int> a, vector<int> b){
	for(unsigned int i=0; i<a.size(); i++){
		if(a[i]!=b[i]) return false;
	}
	return true;
}


//2点間の距離
double P::dist(P a, P b){
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

//template <class T>
void CSVData::save_to(string filename){

}

//template <class T>
void CSVData::load_from(string filename){

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

void folder_check(){
	if(mkdir("all",777)==0){
		cout << "フォルダallを作成しました"<<endl;
		mkdir("all/correlation",777)==0;
		cout << "フォルダall/correlationを作成しました"<<endl;
		mkdir("all/k-means",777)==0;
		cout << "フォルダall/k-meansを作成しました"<<endl;
		mkdir("all/k-means/output",777)==0;
		cout << "フォルダall/k-means/outputを作成しました"<<endl;
		mkdir("all/k-means/graph",777)==0;
		cout << "フォルダall/k-means/graphを作成しました"<<endl;
		mkdir("all/association",777)==0;
		cout << "フォルダall/associationを作成しました"<<endl;
	}



}
