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

using namespace std;

class P{
	public:
		double x, y;
		P(double a, double b){x = a; y= b;};
};

//extern static const double INF;
extern unsigned int index, row_num, col_num;
extern double *csv_data;
extern string *rabel;
extern const int K;//クラスタ数
extern int sheet_num;
extern int rab_x, rab_y;
//extern double SD[K];
extern vector<int> order;

//statistics.cpp
int csv_read(const char *filename);
vector<double> tovec();
double dist(P a, P b);
bool isEqual(vector<int> a, vector<int> b);
void kmeans(const vector<P> &input);
void gnuplot();
void sokan(const vector<P> &input);
void aso(double *input);
int conb(int n, int r);

//priori.cpp
extern const int MIN_SUP;
extern unsigned int row;
extern map<vector<string> , int> C;
extern map<vector<string> , int> L;
void C1(double *input);
void L1();
void generate_C();
void generate_L();
void output(map<vector<string>, int> );
void scan_D();
void prune();
bool check_compatibility(vector<string>, vector<string> );
void set_count(vector<string> );


#endif /* HEADER_H */
