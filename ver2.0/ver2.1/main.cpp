#include "head.hpp"
#include <limits.h>


int main(){

	int sheet_num = 0;
	vector<int> order;
	int level;
	double SD_max[K], SD_min[K];
	ofstream sokanf;//sokan出力用
	ofstream sdf;//k-meansのクラスタごとの標準偏差の出力用

	const string fn = "iris.csv";
	//vector<vector<double> > m_csv_data;
	//vector<string> m_rabel;
	//vector<double> csv;

	CSVData mycsv;
	
	mycsv = CSVData::load_from(fn);

	//Bigdata myBd;
	//csvはvector<double>？CSVDataのオブジェクト？
	//vector<doubleならCSVDataのオブジェクトっていつ作るの？
	//CSVDataのオブジェクトなら静的メンバ関数にする意味は何？>

	//mycsv.load_from(fn);
	//Bigdata mybd(mycsv);
	
	//cout << myBd.col_num() << endl;


	//csv_data = new double[myBd.col_num()*myBd.row_num()];
	cout << "new size:"<< mycsv.col_num * mycsv.row_num << endl;

	/*if(myBd.read(csv_data))//fn->csv_data
		cout<< "csv読み込み完了"<< endl;



	//ベクター型のcsvというコンテナに入力データcsv_data[]を入れる
	if(myBd.tovec(csv_data, csv)){
		cout << "vector変換完了"<<endl;
	}

	cout <<" csv:"<< csv[0] << endl;
*/

	//配列を何個用意しますか？xC2個
	//xC2個のVectorに突っ込んでいく
	int result_num;
	int r = 2;
	result_num = conb(mycsv.col_num, r);

	vector<P> data;
	//int m_row_num =	mycsv.row_num;
	//int m_col_num = mycsv.col_num;
	data.reserve(mycsv.row_num);

	cout << "conb:" << result_num << endl;

	//comb

	for(int i=0;i< mycsv.col_num;i++){
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

	Bigdata myBd;

	//csv.reserve(mycsv.index);

	cout <<"do"<<endl;

	do{
		sokanf << "[ "<<order[0] << "列目と"<<order[1]<< "列目 ]" <<endl;
		sdf << "[ "<<order[0] << "列目と"<<order[1]<< "列目 ]" <<endl;


		//data[行数]に全組み合わせで値入れる
		for(int j = 0 ; j < mycsv.row_num ; j++){
			data[j].x = mycsv.csv_data[j * mycsv.col_num + order[0]];
			data[j].y = mycsv.csv_data[j * mycsv.col_num + order[1]];
		}

		//ここからdata[]に対して3つの統計処理を行う
		//kmeans関数内でgnuplotまでやってる
		//gnuplotで使うrabelの添え字
		myBd.sokan(mycsv, data, sokanf);
		
		myBd.kmeans(mycsv, data, sheet_num, order[0], order[1], SD_max, SD_min, sdf);

		sheet_num++;
	}while(next_combination(order.begin(),order.begin()+r, order.end()));//csv[]の中の順番が変わる

	cout <<"-----------------------------------------"<<endl;
	cout << "相関とk-means終了"<<endl<<endl;

	myBd.aso(mycsv);

	sokanf.close();
	sdf.close();

	//全部計算終わってからじゃないとフィルタリングはできない
	for(int i=0;i<result_num;i++){
		for(int j=0;j<K;j++){
			//filter(level, SD[i][j],i);
		}
	}

	cout << "Complete!!!" <<endl;

	return 0;
}
