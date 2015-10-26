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
string *rabel;
int K = 3; //クラスタ数
int sheet_num = 0;
int rab_x=0, rab_y=0;

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
void kmeans(const vector<P> &input);
void gnuplot();


int conb(int n, int r)
{
	if(n < 0 || r < 0 || n < r) return 0;
	if(!r) return 1;
	return conb(n - 1, r - 1) + conb(n - 1, r);
}

int main(){
	const char *fn = "random.csv";

	vector<double> csv;

	csv_read(fn);
	cout<< "csv読み込み完了"<< endl;
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

/*	cout<<"----------------"<<endl;
	for(int i = 0;i<row_num;i++){
		for(int j=0;j<col_num;j++){
			cout << csv[i*col_num+j] <<" ";
		}
		cout << endl;
	}
*/
	cout << "conb:" << result_num<<endl;

	//comb
	vector<int> order;

	for(int i=0;i< col_num;i++){
		order.push_back(i);
	}

	do{
		//cout << "[ " << order[0];
		for(unsigned int i=0 ; i < r ; i = i + 2){

			cout << "[ "<<order[i] << "行目と"<<order[i+1]<< "行目 ]" <<endl;


			//data[行数]に全組み合わせで値入れる
			for(int j = 0 ; j < row_num ; j++){
				data[j].x = csv[j * col_num + order[i]];
				data[j].y = csv[j * col_num + order[i+1]];
			}

			//ここからdata[]に対して3つの統計処理を行う
			//kmeans関数内でgnuplotまでやってる
			rab_x=order[i];
			rab_y=order[i+1];
			kmeans(data);

		}
		cout <<endl;
		sheet_num++;
	}while(next_combination(order.begin(),order.begin()+r, order.end()));//csv[]の中の順番が変わる

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
	fprintf(gnuplot, "set output \"graph/result%02d.png\"\n",sheet_num);
	fprintf(gnuplot, "set xl \"%s\"\n",rabel[rab_x].c_str());
	fprintf(gnuplot, "set yl \"%s\"\n",rabel[rab_y].c_str());
	fprintf(gnuplot, "plot \"output/out%d.txt\" ",sheet_num);
	for(int i=0;i<K;i++){
		fprintf(gnuplot, "index %d",i);
		if(i!=K-1) fprintf(gnuplot, ", \"\" ");
	}
	fprintf(gnuplot, "\n");
	fprintf(gnuplot, "exit");
	fflush(gnuplot); //バッファを書き出す
	cout << rabel[rab_x]<<"result" << sheet_num << ".png書き込み完了"<<endl;
}

//エントリポイント
void kmeans(const vector<P> &input){

	cout << "kmeans start"<<endl;

	//Kmeansによるクラスタリング
	vector<int> prev_cluster, cluster; //各点のクラスタ番号
	vector<P> vec_m; //各クラスタの代表ベクトル

	for(int i=0; i</*input.size()*/row_num; i++){
		prev_cluster.push_back(0);
		cluster.push_back(-1);
	}

	random_device rnd;     // 非決定的な乱数生成器
	mt19937 mt(rnd());            // メルセンヌ・ツイスタの32ビット版、引数は初期シード
	for (int i = 0; i < K; ++i) {
		int rand = mt()%/*input.size()*/row_num;

		vec_m.push_back(P(0,0));
		vec_m[i]=input[rand];
	}

	while(!isEqual(prev_cluster, cluster)){
		prev_cluster = cluster;

		//入力ベクトルの分割
		for(int i=0; i</*input.size()*/row_num; i++){
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
			for(int j=0; j</*input.size()*/row_num; j++){
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
	stringstream output_name;
	output_name << "output/out" << sheet_num << ".txt";

	ofstream fout;
	fout.open(output_name.str());
	for(int i=0; i<K; i++){
		for(int j=0; j</*input.size()*/row_num; j++){
			if(cluster[j]==i){
				fout << input[j].x << " " << input[j].y << endl;
			}
		}
		fout << endl << endl; //次のクラスタ
	}
	fout.close();

	gnuplot();

}

int csv_read(const char *filename)
{
	ifstream fin,row_num_check;

	rabel = new string[100];

	fin.open(filename);
	if(!fin){
		cout << "ファイルがオープンできません。"<<endl;
	}
	row_num_check.open(filename);

	char buf;

	string line,temp;

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

	//入力ファイルの行数確認
	while(getline(row_num_check,temp)){
		row_num++;
	}
	row_num= row_num-1;
	csv_data = new double[col_num*(row_num)];

	//2行目から読み込む
	while(getline(fin, line)){
		stringstream s2;
		s2 << line;
		//さっき読み込んだ行からカンマまでの読み込みを繰り返す
		while(getline(s2, value, ',')){
			if(value == "\0")//セルが空の場合0を入れる
			{ 
				value = "0";
			}
			stringstream ss(value);
			ss >> csv_data[index];

			index++;
		}
	//	row_num++;
	}

	if(index%row_num!=0)
	{
		cout<<"正しいcsvファイルではありません。縦横のサイズを合わせてください。"<<endl;
		//return -1;
	}
	if(col_num!=index/row_num) cout<<"なにかがおかしい"<<endl;
	cout << "index:"<<index<<" row_num:"<< row_num << " col_num:"<< index/row_num <<endl;

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

	delete [] csv_data;
	return vecsv_data;
}
