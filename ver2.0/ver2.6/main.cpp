#include "bigdata.hpp"
#include "head.hpp"
#include "func.hpp"
#include "filter.hpp"
//#include "check.hpp"

int main(){

	const string fn = "iris.csv";

	CSVData mycsv;
	mycsv.load_from(fn);

	cout << "new size:"<< mycsv.get_col() * mycsv.get_row() << endl;
	cout << "conb:" << conb(mycsv.get_col(),2) << endl;

	folder_check();
	
	all_data mydata;

	//all
	mydata.all(mycsv);//CSVData型をall_data型へ変換。mydataのメンバ変数をいじる。
	
	//フィルタ
	cout <<"-----------------------------------------"<<endl;

	//fil_kmeans(&mydata);
	sort(mydata.mysd.begin(), mydata.mysd.end());
	

	//print(mydata);

	write(mydata);//ファイル書き込み

	cout << "Complete!!!" <<endl;

	return 0;
}
