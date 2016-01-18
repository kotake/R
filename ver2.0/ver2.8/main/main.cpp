#include "main.hpp"
//#include "bigdata.hpp"
//#include "filter.hpp"
//#include "../platform/func.hpp"
//#include "check.hpp"

int main(){

	const string fn = "iris.csv";

	//CSVData mycsv;
	//mycsv.load_from(fn);

	//cout << "new size:"<< mycsv.get_col() * mycsv.get_row() << endl;
	//cout << "conb:" << conb(mycsv.get_col(),2) << endl;

	folder_check();

	/*
	all_data mydata;

	//all
	mydata.all(mycsv);//CSVData型をall_data型へ変換。mydataのメンバ変数をいじる。
	
	//フィルタ
	cout <<"-----------------------------------------"<<endl;

	fil_kmeans(&mydata);
	fil_r(&mydata);
	//sort(mydata.mysd.begin(), mydata.mysd.end());
	

	//print(mydata);

	write(mydata);//ファイル書き込み
*/

	Platform p;
	
	//分析オブジェクト生成
	Sokan *sokan = new Sokan();
	Kmeans *kmeans = new Kmeans();
	Aso *aso = new Aso();
	
	//フィルターオブジェクト生成
	Fil_kmeans *f_kmeans = new Fil_kmeans();
	Fil_r *f_r = new Fil_r();

	//分析オブジェクトをセット
	p.addAnalyzer(sokan);
	p.addAnalyzer(kmeans);
	p.addAnalyzer(aso);

	//フィルターオブジェクトをセット
	//p.addFilter(f_kmeans);
	p.addFilter(f_r);

	//入力データセット
	p.input(fn);

	//実行
	p.execute();
	
	//出力
	p.output();

	cout << "Complete!!!" <<endl;

	delete sokan;
	delete kmeans;
	delete aso;
	delete f_kmeans;
	delete f_r;

	return 0;
}
