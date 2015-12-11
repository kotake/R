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

class P{
	public:
		double x, y;
		P(double a, double b){x = a; y= b;};
		static double dist(P a, P b);
};

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
		int get_col(){return col_num;};
		int get_row(){return row_num;};
		int get_index(){return index;};
};

//all_dataクラスの内包クラス
class sokan_data{//nC2個
	public:
		void set(string r_x, string r_y, double vr);
		//private:
		string rab_x;
		string rab_y;
		double r;
};

//all_dataクラスが内包するkmeans_dataクラスの内包クラス
class point{
	public:
		double x;
		double y;
		int cluster;
};

//all_dataクラスの内包クラス
class kmeans_data{//nC2個
	public:
		//private:
		string rab_x;
		string rab_y;
	public:
		void set(string r_x, string r_y);
		point set(double vx, double vy, int cluster);
		//vector<point> cluster;//K個
		vector<point> p;//全く分からない個
		point pp;
};

//all_dataクラスの内包クラス
class aso_data{//わかんない個
	public:
		void to_var(ifstream &ifs);
		int get_col(ifstream &ifs);
		//private:
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
		void all(CSVData data);
		void set_rabel(CSVData source);

		vector<sokan_data> mysd;
		vector<kmeans_data> mykd;
		vector<aso_data> myad;
};

all_data::all_data(){
	mysd.clear();
	mykd.clear();
	myad.clear();
}

bool isEqual(vector<int> a, vector<int> b);
int conb(int n, int r);

//フィルター関数
void fil_kmeans(all_data data);
void fil_r(all_data data);

#endif /* HEADER_H */
