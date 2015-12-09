#include "bigdata.hpp"
#include "head.hpp"
#include "statistics.hpp"
#include "filter.hpp"

int main(){

	const string fn = "iris.csv";

	CSVData mycsv;
	mycsv = CSVData::load_from(fn);

	cout << "new size:"<< mycsv.get_col() * mycsv.get_row() << endl;

	cout << "conb:" << conb(mycsv.get_col(),2) << endl;

	if(mkdir("all",777)==0){
		cout << "フォルダallを作成しました"<<endl;
		mkdir("all/correlation",777)==0;
		cout << "フォルダall/correlationを作成しました"<<endl;
		mkdir("all/k-means",777)==0;
		cout << "フォルダall/k-meansを作成しました"<<endl;
		mkdir("all/k-means/output",777)==0;
		cout << "フォルダall/k-means/outputを作成しました"<<endl;
		mkdir("all/k-means/graph",777)==0;
		cout << "フォルダall/k-means/graphを作成しました"<<endl;
		mkdir("all/association",777)==0;
		cout << "フォルダall/associationを作成しました"<<endl;
	}

	all_data mydata;
	
	//all
	mydata = all(mycsv);//CSVData型をall_data型へ変換
	
	//フィルタ
	cout <<"-----------------------------------------"<<endl;

	//allからafter_filにコピー
	fil_kmeans(mydata);
	fil_r(mydata);

	write(mydata);//ファイル書き込み

	cout << "Complete!!!" <<endl;

	return 0;
}
