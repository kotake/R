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

//template <class T>
class CSVData{
	public:
		int index;
		int col_num;
		int row_num;
		vector<double> csv_data;
		vector<string> rabel;
	public:
		void  save_to(string filename);
		static CSVData load_from(string filename);
		int get_col(){return col_num;};
		int get_row(){return row_num;};
		int get_index(){return index;};
};

class all_data{
	public:	
		all_data();
	public:
		class sokan_data{//nC2個
			public:
				vector<string> rab_x;
				vector<string> rab_y;
				vector<double> r;
		};
		class kmeans_data{//nC2個
			public:
				vector<string> rab_x;
				vector<string> rab_y;
				vector<double> x;
				vector<double> y;
		};
		class aso_data{//わかんない個
			public:
				vector<string> lhs;
				vector<string> rhs;
				vector<double> support;
				vector<double> confidence;
				vector<double> lift;
		};
	public:
		sokan_data mysd;
		kmeans_data mykd;
		aso_data myad;
};

all_data::all_data(){
	mysd.rab_x.clear();
	mysd.rab_y.clear();
	mysd.r.clear();
	mykd.rab_x.clear();
	mykd.rab_y.clear();
	mykd.x.clear();
	mykd.y.clear();
	myad.lhs.clear();
	myad.rhs.clear();
	myad.support.clear();
	myad.confidence.clear();
	myad.lift.clear();
	//オブジェクト生成
	/*sokan_data mysd;
	  kmeans_data mykd;
	  aso_data myad;
	  */
}


bool isEqual(vector<int> a, vector<int> b);
int conb(int n, int r);
void set_rabel(CSVData source, all_data target);

//void filter();
//vector<ofstream*> filter(string st_name, double r, string sort_name, int data_num);

//フィルター関数
void fil_kmeans(all_data data);
void fil_r(all_data data);

#endif /* HEADER_H */
