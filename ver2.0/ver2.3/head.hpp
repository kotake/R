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
class CSVData
{
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

//template <class T>

class Bigdata{
	public:
		void kmeans(CSVData mycsv);
		void gnuplot(CSVData mycsv, int sheet_num, int rab_x, int rab_y);
		void sokan(CSVData mycsv);
		void aso(CSVData mycsv);

		double SD[K];

	private:
		string line,value;
};

bool isEqual(vector<int> a, vector<int> b);
int conb(int n, int r);

void filter();
//vector<ofstream*> filter(string st_name, double r, string sort_name, int data_num);

class Result{
	double r;//相関係数
	double *r_dp;//kmeans
	string r_st;//association
};


#endif /* HEADER_H */
