
#ifndef HEADER_H
#define HEADER_H

/* ... <header.h> の内容がここに入る */
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <random>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <math.h>
#include "next_permutation.hpp"
#include <map>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>

#define K 3
#define INF 1000000000.0

using namespace std;

class CSVData{//csvファイルの入力数
	private:
		int index;
		int col_num;
		int row_num;
	public:
		vector<double> csv_data;
		vector<string> rabel;
		void save_to(string filename);
		void load_from(string filename);
		int get_col() const{return col_num;};
		int get_row() const{return row_num;};
		int get_index() const{return index;};
};

/////////////////////////////////////

//前方宣言
class all_data;

//分析クラス
class Analyzer{//純粋仮想関数を書く
	public:
		Analyzer() {}
		virtual all_data analyze(const CSVData &mycsv) = 0;
		//vector<Kmeans> kmeans(const CSVData &mycsv);
		//void gnuplot (const Kmeans &k, const int &sheet_num) const;
		//vector<Sokan> sokan(const CSVData &mycsv);
		//vector<Aso> aso(const CSVData &mycsv);
		void into_r(double a){r.push_back(a);};//相関係数

	private:
		string line,value;
		vector<double> r;
};


//all_dataクラスの内包クラス
class Sokan : public Analyzer{//nC2個
	public:
		all_data analyze(const CSVData &mycsv);
		void set(string r_x, string r_y, double vr);
		string get_rab_x()const{return rab_x;};
		string get_rab_y()const{return rab_y;};
		double get_r()const{return r;};
	private:
		string rab_x;
		string rab_y;
		double r;
	public:
		bool operator< (const Sokan& right) const{
			return r == right.r ? rab_x > right.rab_x : r > right.r;
		}
};

//all_dataクラスが内包するkmeans_dataクラスの内包クラス
class P{
	public:
		void set(double vx, double vy, int vc=-1);
		//P set(double x,double y);
		void c_update(int new_c){cluster = new_c;};
		double dist(P v);
		double get_x()const{return x;};
		double get_y()const{return y;};
		int get_cluster()const{return cluster;};
	private:
		double x;
		double y;
		int cluster;
		//static double dist(P a, P b);
};


//all_dataクラスの内包クラス
class Kmeans : public Analyzer{//nC2個
	public:
		all_data analyze(const CSVData &mycsv);
		void set(string r_x, string r_y);
		//P set(P vp, int cluster);
		vector<P> assign_c(vector<P> &p);
		void gnuplot (const Kmeans *k, const int &sheet_num) const;
		string get_rab_x() const{return rab_x;};
		string get_rab_y() const{return rab_y;};
		vector<P> c_vec;//K個
		vector<P> p;//全く分からない個
	private:
		string rab_x;
		string rab_y;
};

//all_dataクラスの内包クラス
class Aso : public Analyzer{//わかんない個
	public:
		all_data analyze(const CSVData &mycsv);
		void to_var(ifstream &ifs);
		int get_col(ifstream &ifs);
		string get_lhs() const{return lhs;};
		string get_rhs() const{return rhs;};
		double get_support() const{return support;};
		double get_confidence() const{return confidence;};
		double get_lift() const{return lift;};

	private:
		string lhs;
		string rhs;
		double support;
		double confidence;
		double lift;
};

//コンポジション
class all_data{
	public:
		all_data();
		//void all(CSVData &data);
		void set_rabel(CSVData source);
	//private:
		vector<Sokan*> mysd;
		vector<Kmeans*> mykd;
		vector<Aso*> myad;
};

all_data::all_data(){
	mysd.clear();
	mykd.clear();
	myad.clear();
}

bool isEqual(vector<int> a, vector<int> b);
int conb(int n, int r);

//フィルタークラス
class Filter{//純粋仮想関数を書く
	public:
		Filter() {}
		virtual all_data filtering(all_data *data) = 0;//なぜか純粋にするとエラー
};

//プラットフォームクラス
class Platform{
	public:
		//Platform()=default;
		void addAnalyzer(Analyzer *a);
		void addFilter(Filter *a);
		void input(string filename);
		void execute();
		void output();
	private:
		list<Analyzer*> analyzer_list;
		list<Filter*> filter_list;
		all_data d;
		CSVData csv;
		//vector<Sokan> mysd;
		//vector<Kmeans> mykd;
		//vector<Aso> myad;
		//ここにmethod()を書く。
		void method1();
		void method2();
};

void Platform::addAnalyzer(Analyzer *a){
	analyzer_list.push_back(a);
}

void Platform::addFilter(Filter *a){
	filter_list.push_back(a);
}

void Platform::input(string filename){
	csv.load_from(filename);
}

void Platform::output(){

}

#endif /* HEADER_H */
