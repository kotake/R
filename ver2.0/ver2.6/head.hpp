#ifndef HEADER_H
#define HEADER_H

/* ... <header.h> の内容がここに入る */
#include <iostream>
#include <vector>
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

//all_dataクラスの内包クラス
class sokan_data{//nC2個
	public:
		void set(string r_x, string r_y, double vr);
		string get_rab_x()const{return rab_x;};
		string get_rab_y()const{return rab_y;};
		double get_r()const{return r;};
	private:
		string rab_x;
		string rab_y;
		double r;
	public:
		bool operator< (const sokan_data& right) const{
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
class kmeans_data{//nC2個
	public:
		void set(string r_x, string r_y);
		//P set(P vp, int cluster);
		vector<P> assign_c(vector<P> &p);
		string get_rab_x() const{return rab_x;};
		string get_rab_y() const{return rab_y;};
		vector<P> c_vec;//K個
		vector<P> p;//全く分からない個
	private:
		string rab_x;
		string rab_y;

};

//all_dataクラスの内包クラス
class aso_data{//わかんない個
	public:
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
		void all(CSVData &data);
		void set_rabel(CSVData source);

		vector<sokan_data> mysd;
		vector<kmeans_data> mykd;
		vector<aso_data> myad;
		//ここにmethod()を書く。
		void method1();
		void method2();
};

all_data::all_data(){
	mysd.clear();
	mykd.clear();
	myad.clear();
}

class Bigdata{
	public:
		vector<kmeans_data> kmeans(const CSVData &mycsv);
		void gnuplot (const kmeans_data &k, const int &sheet_num) const;
		vector<sokan_data> sokan(const CSVData &mycsv);
		vector<aso_data> aso(const CSVData &mycsv);

		void into_r(double a){r.push_back(a);};//相関係数	
	private:
		string line,value;
		vector<double> r;
};

bool isEqual(vector<int> a, vector<int> b);
int conb(int n, int r);

//フィルター関数
//void fil_kmeans(all_data *data);
//void fil_r(all_data *data);

#endif /* HEADER_H */
