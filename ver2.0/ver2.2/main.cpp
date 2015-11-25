#include "head.hpp"

int main(){

	int sheet_num = 0;
	vector<int> order;
	int level;
	double SD_max[K], SD_min[K];
	ofstream sokanf;//sokan出力用
	ofstream sdf;//k-meansのクラスタごとの標準偏差の出力用

	const string fn = "iris.csv";

	CSVData mycsv;
	mycsv = CSVData::load_from(fn);

	cout << "new size:"<< mycsv.get_col() * mycsv.get_row() << endl;

	//配列を何個用意しますか？xC2個
	//xC2個のVectorに突っ込んでいく
	int result_num;
	int r = 2;
	result_num = conb(mycsv.get_col(), r);

	vector<P> data;
	data.reserve(mycsv.get_row());

	cout << "conb:" << result_num << endl;

	//comb

	for(int i=0;i< mycsv.get_col();i++){
		order.push_back(i);
	}

	//sokan用ファイルポインタ
	stringstream output_name;

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

	output_name<< "all/correlation/output.txt";
	sokanf.open(output_name.str());
	sdf.open("all/k-means/standard_deviation.txt");

	//max,min
	for(int i = 0; i < K; i++){
		SD_max[i] = 0;
		SD_min[i] = INT_MAX;
	}


	#pragma omp parallel for
	for(int i=0;i<result_num;i++){//csv[]の中の順番が変わる
	Bigdata myBd;
		sokanf << "[ "<<order[0] << "列目と"<<order[1]<< "列目 ]" <<endl;
		sdf << "[ "<<order[0] << "列目と"<<order[1]<< "列目 ]" <<endl;


		//data[行数]に全組み合わせで値入れる
		for(int j = 0 ; j < mycsv.row_num ; j++){
			data[j].x = mycsv.csv_data[j * mycsv.get_col() + order[0]];
			data[j].y = mycsv.csv_data[j * mycsv.get_col() + order[1]];
		}

		//ここからdata[]に対して3つの統計処理を行う
		//kmeans関数内でgnuplotまでやってる
		//gnuplotで使うrabelの添え字
		myBd.sokan(mycsv, data, sokanf);

		myBd.kmeans(mycsv, data, sheet_num, order[0], order[1], SD_max, SD_min, sdf);
		
		next_combination(order.begin(),order.begin()+r, order.end());
		sheet_num++;
	}
	cout <<"-----------------------------------------"<<endl;
	cout << "相関とk-means終了"<<endl<<endl;

	Bigdata myBd;
	myBd.aso(mycsv);

	sokanf.close();
	sdf.close();

	//フィルタ
	cout <<"-----------------------------------------"<<endl;
	filter();
	
	cout << "Complete!!!" <<endl;

	return 0;
}
