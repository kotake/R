#include "head.hpp"

//この関数で3つの統計処理を行う
void all_data::all(CSVData &data){

	Bigdata mybd;
	//vector<sokan_data> mysd;
	//vector<kmeans_data> mykd;
	//vector<aso_data> myad;

	mysd = mybd.sokan(data);//mydataの中のmysdにアクセス
	mykd = mybd.kmeans(data);//mydataの中のmykdにアクセス
	cout<<"mykd.k[0]:"<< mykd[0].rab_x<<endl;
	
	myad = mybd.aso(data);//all_data::aso_data

}

void sokan_data::set(string r_x, string r_y, double vr){
	rab_x = r_x;
	rab_y = r_y;
	r = vr;
}

vector<sokan_data> Bigdata::sokan(const CSVData &mycsv){
	//cout << "sokan start"<<endl;
	vector<int> order;
	vector<P> input;
	input.reserve(mycsv.get_row());
	for(int x = 0; x < mycsv.get_col(); x++){
		order.push_back(x);
	}
	vector<sokan_data> sokan;//返り値の宣言
	sokan_data s;//これsをsokanにnC2回push_backする

	stringstream output_name;
	output_name << "all/correlation/output.txt";
	ofstream sokanf;
	sokanf.open(output_name.str());
	cout << "sokan conb:"<< conb(mycsv.get_col(),2) <<endl;

	for(int x = 0; x < conb(mycsv.get_col(),2); x++){
		sokanf << "[ " << order[0]<<"列目と"<<order[1]<<"列目 ]"<<endl;
		for(int y=0 ;y < mycsv.get_col() ;y++){
			input[y].x = mycsv.csv_data[y * mycsv.get_col() + order[0]];
			input[y].y = mycsv.csv_data[y * mycsv.get_col() + order[1]];
		}

		double r=0;
		double x_avg=0,y_avg=0;
		double chi=0,mo1=0,mo2=0;
		vector<double> tmp_x,tmp_y;
		for(int i=0; i < mycsv.get_row(); i++){
			tmp_x.push_back(input[i].x);
		}
		x_avg = accumulate(tmp_x.begin(), tmp_x.end(), 0.0)/(double)mycsv.get_row();
		for(int i=0;i<mycsv.get_row();i++){
			tmp_y.push_back(input[i].y);
		}
		y_avg = accumulate(tmp_y.begin(),tmp_y.end(),0.0)/(double)mycsv.get_row();

		for(int i =0;i < mycsv.get_row();i++){
			chi += (input[i].x - x_avg) * (input[i].y - y_avg);
			mo1 += pow((input[i].x - x_avg),2.0);
			mo2 += pow((input[i].y - y_avg),2.0);
		}
		r = chi / (sqrt(mo1)*sqrt(mo2));
		sokanf <<"相関係数:"<< r << endl << endl;
		s.set(mycsv.rabel[order[0]], mycsv.rabel[order[1]], r);
		sokan.push_back(s);

		next_combination(order.begin(),order.begin()+2,order.end());
	}

	sokanf.close();
	return sokan;
}

void kmeans_data::set(string r_x, string r_y){
	rab_x = r_x;
	rab_y = r_y;
}
P kmeans_data::set(double x, double y){
	P p;
	p.x=x;
	p.y=y;
	return p;
}

P kmeans_data::set(P vp, int vc){
	P p;
	p = vp;
	p.cluster = vc;
	return p;
}

//エントリポイント
vector<kmeans_data> Bigdata::kmeans(const CSVData &mycsv){

	//cout << "kmeans start"<<endl;
	double SD_max[K], SD_min[K];
	for(int x=0;x<K;x++){
		SD_max[x] = 0;
		SD_min[x] = INT_MAX;
	}

	vector<kmeans_data> kmeans;//返り値宣言

	//あらかじめこの中にすべてのorderの値を入れておく
	vector<int> order;
	for(int y =0;y<mycsv.get_col();y++){
		order.push_back(y);
	}

	cout << "kmeans conb:"<< conb(mycsv.get_col(),2) <<endl;
	for(int x=0;x<conb(mycsv.get_col(),2);x++){

		kmeans_data k;//nC2個

		k.set(mycsv.rabel[order[0]], mycsv.rabel[order[1]]);

		for(int y=0;y<mycsv.get_row();y++){
			k.p.push_back(k.set(mycsv.csv_data[y*mycsv.get_col()+order[0]], mycsv.csv_data[y*mycsv.get_col()+order[1]]));
		}

		//Kmeansによるクラスタリング
		vector<int> prev_cluster, cluster; //各点のクラスタ番号

		for(int i=0; i<mycsv.get_row(); i++){
			prev_cluster.push_back(0);
			cluster.push_back(-1);
		}

		random_device rnd;     // 非決定的な乱数生成器
		mt19937 mt(rnd());            // メルセンヌ・ツイスタの32ビット版、引数は初期シード
		//クラスタの初期値を入力データからランダムに決定
		for (int i = 0; i < K; ++i) {
			int rand = mt() % mycsv.get_row();

			//vec_m.push_back(P(0,0));
			//vec_m[i] = input[rand];
			k.c_vec.push_back(k.p[rand]);
		}

		//位置が変わらないまで
		while(!isEqual(prev_cluster, cluster)){
			prev_cluster = cluster;

			//入力ベクトルの分割
			for(int i=0; i<mycsv.get_row(); i++){
				int argmax_cluster = -1;
				double argmax_value = INF;
				//一番類似度の高い(距離が一番近い)クラスタにする
				for(int j=0; j<K; j++){
					if(argmax_value > P::dist(k.p[i], k.c_vec[j])){
						argmax_value = P::dist(k.p[i], k.c_vec[j]);
						argmax_cluster = j;
					}
				}
				cluster[i] = argmax_cluster;
				k.p[i].cluster = cluster[i];
			}

			//代表ベクトルの再計算
			for(int i=0; i<K; i++){
				int cnt = 0;
				k.c_vec[i].x = 0;
				k.c_vec[i].y = 0;
				for(int j=0; j < mycsv.get_row(); j++){
					if(cluster[j]==i){
						k.c_vec[i].x += k.p[j].x;
						k.c_vec[i].y += k.p[j].y;
						cnt++;
					}
				}
				if(cnt!=0){
					k.c_vec[i].x /= cnt;
					k.c_vec[i].y /= cnt;
				}
			}
		}


		//結果の出力(gnuplot用)
		stringstream output_name;
		output_name << "all/k-means/output/out" << x << ".txt";

		//クラスタごとに座標をファイルに書き込み
		ofstream fout;
		fout.open(output_name.str());

		for(int i=0; i<K; i++){
			for(int j=0; j<mycsv.get_row(); j++){
				if(cluster[j]==i){
					fout << k.p[j].x << " " << k.p[j].y << endl;
				}
			}
			fout << endl << endl; //次のクラスタ
		}
		fout.close();


		//クラスタごとの標準偏差を計算
		//for(int i=0;i<K;i++){
		//	SD[i] = 0;
		//}
		for(int i = 0; i < K; i++){
			double avg = 0,tmp = 0;
			int count = 0;
			for(int j = 0; j < mycsv.get_row(); j++){
				if(cluster[j]==i){
					tmp += P::dist(k.p[j], k.c_vec[i]);
					count++;
				}
			} 
			avg = tmp / (double)count;
			tmp = 0;
			for(int j = 0; j < mycsv.get_row(); j++){
				double hensa = P::dist(k.p[j],k.c_vec[i]) - avg;
				tmp += hensa * hensa;
				//SD[i] = sqrt(tmp / (double)count);
			}
		}

		//max,min
		//for(int i = 0; i < K; i++){
		//	if(SD_max[i] < SD[i]) SD_max[i] = SD[i];
		//	if(SD_min[i] > SD[i]) SD_min[i] = SD[i];
		//}

		//for(int i = 0; i < K; i++){
		//	sdf << "クラスタ["<<i<<"]の標準偏差:"<< SD[i] << "	現在--->最大値:" << SD_max[i] <<" 最小値:" << SD_min[i] << endl;
		//}
		//sdf << endl;

		gnuplot(mycsv, x, order[0], order[1]);

		kmeans.push_back(k);
		//cout << k.p[0].x << endl;

		next_combination(order.begin(),order.begin()+2,order.end());
	}

	cout << "p.rab:"<< kmeans[0].rab_x<<", "<<kmeans[0].rab_y<<endl;
	cout << "p.size():"<< kmeans[0].p.size()<<endl;
	cout << "x:"<< kmeans[0].p[0].x <<endl;
	cout << "y:"<< kmeans[0].p[0].y <<endl;

	cout << "c_vec.size():"<< kmeans[0].c_vec.size()<<endl;

	//sdf.close();
	return kmeans;
}

//Rのアソシエーション分析出力結果専用の行数カウント関数
int aso_data::get_col(ifstream &ifs){

	int num = 0;
	string s;

	for(int i=1;!ifs.eof();i++){
		ifs >> s;

		//string => int
		stringstream ss;
		int si;
		ss << s;
		ss >> si;

		//読み込んだ文字が行数と一致していたら
		if(si == num+1){
			num++;
		};
	}
	return num;
}

void aso_data::to_var(ifstream &ifs){
	string s, tmp;

	//ワードを一つずつ拾う
	for(int i=0;i < 7;i++){
		ifs >> s;

		//もし末文字が,なら
		while(s[s.size()-1] == ','){
			tmp = s;
			ifs >> s;
			s = tmp + s;
		};


		if(i==0)continue;
		if(i==1)lhs = s;
		if(i==2)continue;
		if(i==3)rhs = s;
		if(i==4){
			stringstream sss;
			double d;
			sss << s;
			sss >> d;
			support = d;
		}
		if(i==5){
			stringstream sss;
			double d;
			sss << s;
			sss >> d;
			confidence = d;
		}
		if(i==6){
			stringstream sss;
			double d;
			sss << s;
			sss >> d;
			lift = d;
		}
	}

}

vector<aso_data> Bigdata::aso(const CSVData &mycsv){

	double d[mycsv.get_index()];
	cout << "aso start" << endl;
	for(int i = 0; i < mycsv.get_index(); i++){
		d[i] = mycsv.csv_data[i];
	}

	//岡システム
	double sum, avg;
	ofstream ofs2("all/association/transaction.txt");

	for(int i=0; i < mycsv.get_row(); i++){
		//1行ごとに処理
		sum = 0.0;
		for(int j = 0; j < mycsv.get_col(); j++){
			sum += d[i*mycsv.get_col()+j];
		}

		avg = sum/mycsv.get_col();
		for(int j=0;j<mycsv.get_col();j++){
			if(d[i*mycsv.get_col()+j]>avg){
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

	vector<aso_data> aso;//返り値宣言
	aso_data a;

	ifstream ifs("all/association/foo.txt");

	//ifs行数取得	
	int col = 0;
	col = a.get_col(ifs);
	cout << col<<endl;
	ifs.clear();
	ifs.seekg(0,ios_base::beg);

	//1行目スキップ
	string line, st;
	getline(ifs,line);

	//2行目以降
	for(int i = 0; i < col; i++){
		a.to_var(ifs);
		aso.push_back(a);
	}

	ifs.close();
	/*
	   RInside R;
	   R.parseEval("suppressMessages(library(\"arules\"))");
	   R.parseEval("iris.tran<-read.transactions(file='/home/s-kotake/R/ver2.0/ver2.2/all/association/transaction.txt',sep=',',format='basket')");
	   R.parseEval("iris.ap<-apriori(iris.tran)");
	   R.parseEval("sink(file = \"foo.txt\")");
	   R.parseEval("capture.output(inspect(iris.ap))");
	   R.parseEval("sink()");
	   */
	return aso;
}

void Bigdata::gnuplot(const CSVData &mycsv, const int &sheet_num, const int &rab_x, const int &rab_y) const
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
