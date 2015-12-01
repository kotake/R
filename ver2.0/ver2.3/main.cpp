#include "head.hpp"

int main(){

	const string fn = "iris.csv";

	CSVData mycsv;
	mycsv = CSVData::load_from(fn);

	cout << "new size:"<< mycsv.get_col() * mycsv.get_row() << endl;

	vector<P> data;
	data.reserve(mycsv.get_row());

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
	};

	Result sokan, kmeans, aso;

	Bigdata myBd;
	myBd.sokan(mycsv);

	myBd.kmeans(mycsv);

	cout <<"-----------------------------------------"<<endl;
	cout << "相関とk-means終了"<<endl<<endl;

	myBd.aso(mycsv);


	//フィルタ
	cout <<"-----------------------------------------"<<endl;
	//filter();

	cout << "Complete!!!" <<endl;

	return 0;
}
