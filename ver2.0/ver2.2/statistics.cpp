#include "head.hpp"

int conb(int n, int r)
{
	if(n < 0 || r < 0 || n < r) return 0;
	if(!r) return 1;
	return conb(n - 1, r - 1) + conb(n - 1, r);
}

//収束判定(各点が属するクラスタが変化しないかどうか)
bool isEqual(vector<int> a, vector<int> b){
	for(int i=0; i<a.size(); i++){
		if(a[i]!=b[i]) return false;
	}
	return true;
}


//2点間の距離
double P::dist(P a, P b){
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

void Bigdata::gnuplot(CSVData mycsv, int sheet_num, int rab_x, int rab_y)
{
	FILE* gnuplot = popen("gnuplot", "w");
	fprintf(gnuplot, "set term png\n");	fprintf(gnuplot, "set output \"all/k-means/graph/result%02d.png\"\n",sheet_num);
	fprintf(gnuplot, "set xl \"%s\"\n", mycsv.rabel[rab_x].c_str());
	fprintf(gnuplot, "set yl \"%s\"\n", mycsv.rabel[rab_y].c_str());
	fprintf(gnuplot, "plot \"all/k-means/output/out%d.txt\" ",sheet_num);
	for(int i=0;i<K;i++){
		fprintf(gnuplot, "index %d",i);
		if(i!=K-1) fprintf(gnuplot, ", \"\" ");
	}
	fprintf(gnuplot, "\n");
	fprintf(gnuplot, "exit");
	fflush(gnuplot); //バッファを書き出す
	pclose(gnuplot);
}

void Bigdata::sokan(CSVData mycsv, const vector<P> &input, ofstream &sokanf){
	//cout << "sokan start"<<endl;

	double r=0;
	double x_avg=0,y_avg=0;
	double chi=0,mo1=0,mo2=0;
	vector<double> tmp_x,tmp_y;
	for(int i=0; i < mycsv.row_num; i++){
		tmp_x.push_back(input[i].x);
	}
	x_avg = accumulate(tmp_x.begin(), tmp_x.end(), 0.0)/(double)mycsv.row_num;
	for(int i=0;i<mycsv.row_num;i++){
		tmp_y.push_back(input[i].y);
	}
	y_avg = accumulate(tmp_y.begin(),tmp_y.end(),0.0)/(double)mycsv.row_num;

	for(int i =0;i < mycsv.row_num;i++){
		chi += (input[i].x - x_avg) * (input[i].y - y_avg);
		mo1 += pow((input[i].x - x_avg),2.0);
		mo2 += pow((input[i].y - y_avg),2.0);
	}
	r = chi / (sqrt(mo1)*sqrt(mo2));
	sokanf <<"相関係数:"<< r << endl << endl;

}

//エントリポイント
void Bigdata::kmeans(CSVData mycsv, const vector<P> &input, int sheet_num, int rab_x, int rab_y, double *SD_max, double *SD_min, ofstream &sdf){

	//cout << "kmeans start"<<endl;

	//Kmeansによるクラスタリング
	vector<int> prev_cluster, cluster; //各点のクラスタ番号
	vector<P> vec_m; //各クラスタの代表ベクトル

	for(int i=0; i</*input.size()*/mycsv.row_num; i++){
		prev_cluster.push_back(0);
		cluster.push_back(-1);
	}

	random_device rnd;     // 非決定的な乱数生成器
	mt19937 mt(rnd());            // メルセンヌ・ツイスタの32ビット版、引数は初期シード
	for (int i = 0; i < K; ++i) {
		int rand = mt() % mycsv.row_num;

		vec_m.push_back(P(0,0));
		vec_m[i] = input[rand];
	}



	while(!isEqual(prev_cluster, cluster)){
		prev_cluster = cluster;

		//入力ベクトルの分割
		for(int i=0; i<mycsv.row_num; i++){
			int argmax_cluster = -1;
			double argmax_value = INF;
			//一番類似度の高い(距離が一番近い)クラスタにする
			for(int j=0; j<K; j++){
				if(argmax_value > P::dist(input[i], vec_m[j])){
					argmax_value = P::dist(input[i], vec_m[j]);
					argmax_cluster = j;
				}
			}
			cluster[i] = argmax_cluster;
		}

		//代表ベクトルの再計算
		for(int i=0; i<K; i++){
			int cnt = 0;
			vec_m[i].x = 0;
			vec_m[i].y = 0;
			for(int j=0; j < mycsv.row_num; j++){
				if(cluster[j]==i){
					vec_m[i].x += input[j].x;
					vec_m[i].y += input[j].y;
					cnt++;
				}
			}
			if(cnt!=0){
				vec_m[i].x /= cnt;
				vec_m[i].y /= cnt;
			}
		}
	}


	//結果の出力(gnuplot用)
	stringstream output_name;
	output_name << "all/k-means/output/out" << sheet_num << ".txt";

	//クラスタごとに座標をファイルに書き込み
	ofstream fout;
	fout.open(output_name.str());
	for(int i=0; i<K; i++){
		for(int j=0; j<mycsv.row_num; j++){
			if(cluster[j]==i){
				fout << input[j].x << " " << input[j].y << endl;
			}
		}
		fout << endl << endl; //次のクラスタ
	}
	fout.close();

	//クラスタごとの標準偏差を計算
	for(int i=0;i<K;i++){
		SD[i] = 0;
	}
	for(int i = 0; i < K; i++){
		double avg = 0,tmp = 0;
		int count = 0;
		for(int j = 0; j < mycsv.row_num; j++){
			if(cluster[j]==i){
				tmp += P::dist(input[j], vec_m[i]);
				count++;
			}
		} 
		avg = tmp / (double)count;
		tmp = 0;
		for(int j = 0; j < mycsv.row_num; j++){
			double hensa = P::dist(input[j],vec_m[i]) - avg;
			tmp += hensa * hensa;
			SD[i] = sqrt(tmp / (double)count);
		}
	}

	//max,min
	for(int i = 0; i < K; i++){
		if(SD_max[i] < SD[i]) SD_max[i] = SD[i];
		if(SD_min[i] > SD[i]) SD_min[i] = SD[i];
	}

	for(int i = 0; i < K; i++){
		sdf << "クラスタ["<<i<<"]の標準偏差:"<< SD[i] << "	現在--->最大値:" << SD_max[i] <<" 最小値:" << SD_min[i] << endl;
	}
	sdf << endl;

	gnuplot(mycsv, sheet_num, rab_x, rab_y);
}

//template <class T>
void CSVData::save_to(string filename){

}

//template <class T>
CSVData CSVData::load_from(string filename){

	CSVData object;

	ifstream fin, row_num_check;
	fin.open(filename);

	if(!fin){
		cout << "ファイルがオープンできません。"<<endl;
	}
	row_num_check.open(filename);

	char buf;

	string line,temp;

	object.col_num = 0;
	object.row_num = 0;
	object.index = 0;

	//1行目をrabelとして読み込む
	getline(fin,line);
	stringstream s1;
	s1<<line;
	string value;
	while(getline(s1,value,','))
	{	
		if(value == "\0")//セルが空の場合0を入れる
		{ 
			value = "0";
		}

		object.rabel.push_back(value);
		object.col_num++;
	}	

	cout<<"col_num:"<< object.col_num <<endl;;

	//入力ファイルの行数確認
	while(getline(row_num_check,temp)){
		object.row_num++;
	}
	object.row_num = object.row_num - 1;



	//2行目から読み込む
	while(getline(fin, line)){
		stringstream s2;
		s2 << line;
		double d;
		//さっき読み込んだ行からカンマまでの読み込みを繰り返す
		while(getline(s2, value, ',')){
			if(value == "\0")//セルが空の場合0を入れる
			{ 
				value = "0";
			}
			stringstream ss(value);
			ss >> d;
			object.csv_data.push_back(d);

			object.index++;
		}
	}

	if(object.index % object.row_num!=0)
	{
		cout<<"正しいcsvファイルではありません。縦横のサイズを合わせてください。"<<endl;
	}

	if(object.col_num != object.index / object.row_num) cout<<"なにかがおかしい"<<endl;
	cout << "index:"<<object.index<<" row_num:"<< object.row_num << " col_num:"<< object.index / object.row_num << endl;
	return object;
}

void Bigdata::aso(CSVData mycsv){

	double d[mycsv.index];
	cout << "aso start" << endl;
	for(int i = 0; i < mycsv.index; i++){
		d[i] = mycsv.csv_data[i];
	}

	//岡システム
	double sum, avg;
	ofstream ofs2("all/association/transaction.txt");

	for(int i=0; i < mycsv.row_num; i++){
		//1行ごとに処理
		sum = 0.0;
		for(int j = 0; j < mycsv.col_num; j++){
			sum += d[i*mycsv.col_num+j];
		}

		avg = sum/mycsv.col_num;
		for(int j=0;j<mycsv.col_num;j++){
			if(d[i*mycsv.col_num+j]>avg){
				ofs2 << mycsv.rabel[j] << ",";
			}
		}
		ofs2 << endl;
	}
	ofs2.close();


	FILE *R = popen("R --vanilla --slave","w");
	fprintf(R, "suppressMessages(library(\"arules\"))\n");
	fprintf(R, "iris.tran<-read.transactions(file='all/association/transaction.txt',sep=',',format='basket')\n");
	fprintf(R, "invisible(capture.output(iris.ap<-apriori(iris.tran)))\n");
	fprintf(R, "sink(file = \"all/association/foo.txt\")\n");
	//fprintf(R, "suppressWarnings(inspect(head(SORT(iris.ap, by = \"support\"),n=6)))\n");
	fprintf(R, "suppressWarnings(inspect(iris.ap))\n");
	fprintf(R, "sink()\n");
	fprintf(R, "q(\"no\")\n");
	fflush(R);
	//(void)pclose(R);
}


//filterフォルダ内のファイル(中身はLinuxコマンド、シェルスクリプトみたいな)
void filter(){
	if(mkdir("after_fil",777)==0)
		cout << "フォルダafter_filを作成しました"<<endl;

	//filterフォルダ内の全ファイル一覧取得
	FILE *ls;
	ls = popen("ls filter/","r");
	vector<string> fil_fn;
	char buf[256];//一行を格納 //コマンドライン出力をゲット
	char *c;
	while(c = fgets(buf, sizeof(buf), ls)){
		strtok(buf, "\n\0");
		fil_fn.push_back(buf);
	}

	//filter1ファイルごとの処理
	for(int i=0; i < fil_fn.size(); i++){
		fil_fn[i] = "filter/" + fil_fn[i];
		cout <<"\""<< fil_fn[i] <<"\""<< endl;

		//1ファイルポインタfilの行をfil_fに読み込む
		ifstream fil;
		fil.open(fil_fn[i]);//filterフォルダ内のファイルポインタ取得
		if(!fil){
			cout <<"dont open file"<<endl;
		}

		string line;
		vector<string> fil_f;//１ファイル内のコマンド行数ごとに格納される

		//filter読み込む
		while(getline(fil, line)){
			fil_f.push_back(line);
		}
		fil.close();

		//読み込んだ行をパイプにつなぐ
		vector<string>::iterator it;
		int fil_i = 0;

		for(it = fil_f.begin(); it != fil_f.end(); it++ ){

			FILE *fil_row;
			if( (fil_row = popen(fil_f[fil_i].c_str(),"r")) == NULL){
				perror("can not exec command");
				exit(EXIT_FAILURE);
			}
			else{//エラーがでない場合
				printf("$ %s\n",fil_f[fil_i].c_str());//コマンドライン入力を出力
				char buf[256];//コマンドライン出力をゲット
				char *c;
				while(c = fgets(buf,sizeof(buf),fil_row)){
					printf(">> %s",buf);
				}
			}
			fil_i++;
			pclose(fil_row);
		}
		cout << endl;
	}
}
