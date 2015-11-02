#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include<algorithm>

using namespace std;

class P{
	public:
		string name, sum;
		P(string a, string b){name = a; sum = b;};
};

int main(void){

	ifstream fin;
	
	fin.open("sample.csv");

	int index = 0;
	string line, value;
	string *csv_data;
	csv_data = new string[100];
	while(getline(fin, line)){
		stringstream s1(line);
		//stringstram s1;
		//s1 << line;とも書ける
		while(getline(s1, value,',')){
			stringstream ss(value);//ssにvalueを読み取らせる
			ss >> csv_data[index];
			index++;
		}
	}
	
	int sum = index;
	index=1;

	for(int i=0;i<sum;i++){
		cout << csv_data[i] << endl;
	}
	cout << "sum:" << sum << endl;

	
	//stringからvectorに変換
	vector<string> item;
	for(int i = 0; i < sum;i++){
		item.push_back(csv_data[i]);
	}
	
	cout << "----vectorにした"<<endl;
	for(int i=0;i<item.size() ;i++){
		cout << item[i] << endl;
	}


	sort(item.begin(),item.end());
	item.erase( unique(item.begin(), item.end()),item.end() );
	
	cout << "-----ソート完了"<<endl;
	for(int i=0;i<item.size() ;i++){
		cout << item[i] << endl;
	}

	//それぞれのアイテムの数を数える
	vector<int> item_sum;
	//初期化
	for(int i=0;i<item.size();i++){
		item_sum.push_back(0);
	}
	for(int i=0;i<item.size();i++){
		for(int j= 0;j<sum;j++){
			if(item[i]==csv_data[j]){
				item_sum[i]++;
			}
		}
	}

	for(int i=0;i<item.size();i++){
		cout << item[i]<< "(" <<item_sum[i]<<")"<<endl;
	}

	int minsup = 1, minconf = 1;
	
	for(int i=0;i<item.size();i++){
		if(minsup >= item_sum[i]){
			cout<<"if入った"<<endl;
			item.erase(item.begin()+i);
			item_sum.erase(item_sum.begin()+i);
		}
	}

	cout << "-------------" << endl;
	for(int i=0;i<item.size();i++){
		cout << item[i]<< "(" <<item_sum[i]<<")"<<endl;
	}

	//アイテム数2の支持率
	while(getline(fin, line)){
		stringstream s1(line);
		string tmp[item.size()];
		//stringstram s1;
		//s1 << line;とも書ける
		int col_order = 0;
		while(getline(s1, value,',')){
			stringstream ss(value);//ssにvalueを読み取らせる
			ss >> tmp[col_order];	
			col_order++;
		}
		//一行内で処理ルールに一致しているか
		//tmp == ;
	}

}	
