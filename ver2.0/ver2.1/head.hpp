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
		//CSVData();
		//CSVData(vector<string> f_rabel, vector<double> f_csv_data);
		void  save_to(string filename);
		static CSVData load_from(string filename);
};

class Bigdata{
	public:
		//bool tovec(double *csv_data, vector<double> &vecsv_data);
		void kmeans(CSVData mycsv, const vector<P> &data, int sheet_num, int rab_x, int rab_y, double *SD_max, double *SD_min, ofstream &sdf);
		void gnuplot(CSVData mycsv, int sheet_num, int rab_x, int rab_y);
		void sokan(CSVData mycsv, const vector<P> &data, ofstream &sokanf);
		void aso(CSVData mycsv);

		//constexpr static const double INF = 1000000000.0;
		//unsigned int _index = 0, _row_num = 0, _col_num = 0;
		//string *rabel;

		//int rab_x = 0, rab_y = 0;
		double SD[K];

		//Bigdata(CSVData mycsv);
			
	private:
		//ifstream fin,row_num_check;
		string line,value;
		//CSVData mycsv;
};

/*
   class Csv : public Bigdata{
   public:
   bool get(const char *filename);
   bool read(double *csv_data);
   private:
   ifstream fin,row_num_check;
   string line,value;
   };

   class Rtn : public Bigdata{
   public:
   int row_num();
   int col_num();
   int index();
   };
   */

bool isEqual(vector<int> a, vector<int> b);
int conb(int n, int r);

#endif /* HEADER_H */
