#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include "next_permutation.hpp"

using namespace std;

static const double INF = 1000000000.0;

unsigned int index = 0,row_num=0,col_num=0;
double *csv_data;

//平面ベクトルデータ
class P{
	public:
		double x, y;
		P(double a,double b){x = a; y = b;};
};


int csv_read(const char *filename);
vector<double> tovec();
double dist(P a, P b);
bool isEqual(vector<int> a, vector<int> b);
void gnuplot();

int conb(int n, int r)
{
	if(n < 0 || r < 0 || n < r) return 0;
	if(!r) return 1;
	return conb(n - 1, r - 1) + conb(n - 1, r);
}

int main(){
	const char *fn = "test.csv";

	//vector<double> csv[100];
	vector<double> csv;

	csv_read(fn);
	csv.reserve(index);

	//ベクター型のcsvというコンテナに入力データcsv_data[]を入れる
	csv = tovec();

	//配列を何個用意しますか？xC2個
	//xC2個のVectorに突っ込んでいく
	int result_num;
	int r = 2;
	result_num=conb(col_num, r);

	vector<P> data;
	data.reserve(row_num);

	/*for(int i=1;i<;i++){
	//vector<double> data[n];
	//data[n].reserve(row_num*2);

	//ここを治す
	//for(int i=0;i<;i++){
	//data[n].x.push_back(csv[i]);
	//data[n].y.push_back(csv[i+n]);
	//data.push_back(P(csv[i], csv[i+1]));
	//}
	//data.push_back(0);
	//data.

	}*/

	cout<<"----------------"<<endl;
	for(int i = 0;i<row_num;i++){
		for(int j=0;j<col_num;j++){
			cout << csv[i*col_num+j] <<" ";
		}
		cout << endl;
	}

	cout << "conb:" << result_num<<endl;


	cout << "ここまできてる？"<<endl;

	//comb
	vector<int> order;
	for(int i=0;i< col_num;i++){
		order.push_back(i);
	}

	do{
		//cout << "[ " << order[0];
		for(unsigned int i=0, j=0;i < r ;i=i+2,j++){
			//data[i].x = csv[j];
			//j++;
			//data[i].y = csv[j];
			//cout << "[" << data[i].x << " , " << data[i].y << "]" << endl;
			cout << "[ "<<order[i] << ", "<<order[i+1]<< " ]" <<endl;


			//[1,2]
			for(int k= 0;k<row_num;k++){
				data[k].x = csv[k*col_num+order[i]];
				data[k].y = csv[k*col_num+order[i+1]];
			}

			for(int k =0;k<row_num;k++){
				cout <<"data["<< k <<"]:{"<<data[k].x <<","<<data[k].y<<"}"<<endl;
			}
		}
		cout <<endl;
	}while(next_combination(order.begin(),order.begin()+r, order.end()));//csvの中の順番が変わる



	return 0;
}



//2点間の距離
double dist(P a, P b){
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

//収束判定(各点が属するクラスタが変化しないかどうか)
bool isEqual(vector<int> a, vector<int> b){
	for(int i=0; i<a.size(); i++){
		if(a[i]!=b[i]) return false;
	}
	return true;
}

void gnuplot()
{
	FILE* gnuplot = popen("gnuplot", "w");
	fprintf(gnuplot, "set term png\n");
	fprintf(gnuplot, "set output \"result.png\"\n");
	fprintf(gnuplot, "plot \"out.txt\" index 0, \"\" index 1, \"\" index 2\n");
	fprintf(gnuplot, "exit");
	fflush(gnuplot); //バッファを書き出す
}

//エントリポイント
int kmeans(){

	//入力データ
	vector<P> input;
	double x, y;
	while(cin >> x >> y){
		input.push_back((P){x,y});
	}

	//Kmeansによるクラスタリング
	int K = 3; //クラスタ数
	vector<int> prev_cluster, cluster; //各点のクラスタ番号
	vector<P> vec_m; //各クラスタの代表ベクトル

	for(int i=0; i<input.size(); i++){
		prev_cluster.push_back(0);
		cluster.push_back(-1);
	}

	random_device rnd;     // 非決定的な乱数生成器
	mt19937 mt(rnd());            // メルセンヌ・ツイスタの32ビット版、引数は初期シード
	for (int i = 0; i < K; ++i) {
		int rand = mt()%input.size();

		vec_m.push_back(P(0,0));
		vec_m[i]=input[rand];
	}

	while(!isEqual(prev_cluster, cluster)){
		prev_cluster = cluster;

		//入力ベクトルの分割
		for(int i=0; i<input.size(); i++){
			int argmax_cluster = -1;
			double argmax_value = INF;
			//一番類似度の高い(距離が一番近い)クラスタにする
			for(int j=0; j<K; j++){
				if(argmax_value > dist(input[i], vec_m[j])){
					argmax_value = dist(input[i], vec_m[j]);
					argmax_cluster = j;
				}
			}
			cluster[i] = argmax_cluster;
		}

		//代表ベクトルの再計算
		for(int i=0; i<K; i++){
			int cnt = 0;
			vec_m[i].x = 0;
			vec_m[i].y = 0;
			for(int j=0; j<input.size(); j++){
				if(cluster[j]==i){
					vec_m[i].x += input[j].x;
					vec_m[i].y += input[j].y;
					cnt++;
				}
			}
			if(cnt!=0){
				vec_m[i].x /= cnt;
				vec_m[i].y /= cnt;
			}
		}
	}

	//結果の出力(gnuplot用)
	ofstream fout;
	fout.open("out.txt");
	for(int i=0; i<K; i++){
		for(int j=0; j<input.size(); j++){
			if(cluster[j]==i){
				fout << input[j].x << " " << input[j].y << endl;
			}
		}
		fout << endl << endl; //次のクラスタ
	}
	fout.close();

	gnuplot();

	return 0;
}

int csv_read(const char *filename)
{
	ifstream fin;
	char ch;

	string *rabel;
	rabel = new string[100];

	fin.open(filename);
	if(!fin){
		cout << "ファイルがオープンできません。"<<endl;
	}

	char buf;

	string line;

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

	csv_data = new double[1000];

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

	/*
	   for(int i=0;i<col_num;i++){
	   cout << "rabel["<<i<<"]address:"<<&rabel[i]<<" 中身:"<<rabel[i] << endl;
	   }

	   for(int i=0;i<index;i++){
	   cout << "csv_data["<<i<<"]address:"<<&csv_data[i]<<" 中身:"<<csv_data[i] << endl;
	   }

	   fin.close();
	   */
	return 0;
}


//csv_data[]をvectorに入れる
vector<double> tovec()
{
	vector<double> vecsv_data;
	vecsv_data.reserve(index);
	for(int i=0;i<index;i++){
		vecsv_data.push_back(csv_data[i]);
	}

	/*
	   for(int i=0;i<index;i++){
	   cout << "vecsv_data["<<i<<"]address:"<<&vecsv_data[i]<<" 中身:"<< vecsv_data[i] << endl;
	   }*/

	delete [] csv_data;
	return vecsv_data;
}


