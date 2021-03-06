#include "head.hpp"

//この関数で3つの統計処理を行う
void Platform::execute(){

	//Bigdata mybd;
	all_data tmp;

	//mysd = mybd.sokan(data);//mydataの中のmysdにアクセス
	//mykd = mybd.kmeans(data);//mydataの中のmykdにアクセス
	//myad = mybd.aso(data);//all_data::aso_data

	list<Analyzer*>::iterator it_a = analyzer_list.begin();
	for(int i=0;it_a!=analyzer_list.end();it_a++,i++){
		tmp = (*it_a)->analyze(csv);//親all_data＝子all_data
		if(tmp.mysd.size()!=0){
			d.mysd = tmp.mysd;
		}
		if(tmp.mykd.size()!=0){
			d.mykd = tmp.mykd;
		}
		if(tmp.myad.size()!=0){
			d.myad = tmp.myad;
		}
	}

	list<Filter*>::iterator it_f = filter_list.begin();
	for(;it_f != filter_list.end();it_f++){
		d = (*it_f)->filtering(&d);
	}
}

void Sokan::set(string r_x, string r_y, double vr){
	rab_x = r_x;
	rab_y = r_y;
	r = vr;
}

void P::set(double vx,double vy, int vc){
	x = vx;
	y = vy;
	cluster = vc;
}



all_data Sokan::analyze(const CSVData &mycsv){
	//vector<all_data> Sokan::analyze(const CSVData &mycsv){
	//cout << "sokan start"<<endl;
	vector<int> order;
	vector<P> input;
	input.reserve(mycsv.get_row());
	for(int x = 0; x < mycsv.get_col(); x++){
		order.push_back(x);
	}
	vector<Sokan*> sokan;//返り値の宣言
	Sokan* s = new Sokan();//これsをsokanにnC2回push_backする

	stringstream output_name;
	output_name << "all/correlation/output.txt";
	ofstream sokanf;
	sokanf.open(output_name.str());
	cout << "sokan conb:"<< conb(mycsv.get_col(),2) <<endl;

	for(int x = 0; x < conb(mycsv.get_col(),2); x++){
		sokanf << "[ " << order[0]<<"列目と"<<order[1]<<"列目 ]"<<endl;
		for(int y=0 ;y < mycsv.get_col() ;y++){
			input[y].set(mycsv.csv_data[y * mycsv.get_col() + order[0]],
					mycsv.csv_data[y * mycsv.get_col() + order[1]]);
		}

		double r=0;
		double x_avg=0,y_avg=0;
		double chi=0,mo1=0,mo2=0;
		vector<double> tmp_x,tmp_y;
		for(int i=0; i < mycsv.get_row(); i++){
			tmp_x.push_back(input[i].get_x());
		}
		x_avg = accumulate(tmp_x.begin(), tmp_x.end(), 0.0)/(double)mycsv.get_row();
		for(int i=0;i<mycsv.get_row();i++){
			tmp_y.push_back(input[i].get_y());
		}
		y_avg = accumulate(tmp_y.begin(),tmp_y.end(),0.0)/(double)mycsv.get_row();

		for(int i =0;i < mycsv.get_row();i++){
			chi += (input[i].get_x() - x_avg) * (input[i].get_y() - y_avg);
			mo1 += pow((input[i].get_x() - x_avg),2.0);
			mo2 += pow((input[i].get_y() - y_avg),2.0);
		}
		r = chi / (sqrt(mo1)*sqrt(mo2));
		sokanf <<"相関係数:"<< r << endl << endl;
		s->set(mycsv.rabel[order[0]], mycsv.rabel[order[1]], r);
		sokan.push_back(s);

		next_combination(order.begin(),order.begin()+2,order.end());
	}

	sokanf.close();

	all_data a;
	a.mysd = sokan;
	return a;
}

void Kmeans::set(string r_x, string r_y){
	rab_x = r_x;
	rab_y = r_y;
}
//自分とvとの距離
double P::dist(const P v){
	return sqrt((x-v.x)*(x-v.x) + (y-v.y)*(y-v.y));
}

vector<P> Kmeans::assign_c(vector<P> &p){

	//Kmeansによるクラスタリング
	vector<int> prev_cluster, cluster; //各点のクラスタ番号

	for(int i=0; i<p.size(); i++){
		prev_cluster.push_back(0);
		cluster.push_back(-1);
	}

	random_device rnd;     // 非決定的な乱数生成器
	mt19937 mt(rnd());            // メルセンヌ・ツイスタの32ビット版、引数は初期シード
	//クラスタの初期値を入力データからランダムに決定
	for (int i = 0; i < K; ++i) {
		int rand = mt() % p.size();

		c_vec.push_back(p[rand]);
	}

	//位置が変わらないまで
	while(!isEqual(prev_cluster, cluster)){
		prev_cluster = cluster;

		//入力ベクトルの分割
		for(int i=0; i<p.size(); i++){
			int argmax_cluster = -1;
			double argmax_value = INF;
			//一番類似度の高い(距離が一番近い)クラスタにする
			for(int j=0; j<K; j++){
				if(argmax_value > p[i].dist(c_vec[j])){
					argmax_value = p[i].dist(c_vec[j]);
					argmax_cluster = j;
				}
			}
			cluster[i] = argmax_cluster;
			p[i].c_update(cluster[i]);
		}

		//代表ベクトルの再計算
		for(int i=0; i<K; i++){
			int cnt = 0;
			//k.c_vec[i].x = 0;
			//k.c_vec[i].y = 0;
			double cx = 0, cy = 0;
			for(int j=0; j < p.size(); j++){
				if(cluster[j]==i){
					cx += p[j].get_x();
					cy += p[j].get_y();
					cnt++;
				}
			}
			if(cnt!=0){
				cx /= cnt;
				cy /= cnt;
			}
			c_vec[i].set(cx,cy);
		}
	}

	return c_vec;
}



//エントリポイント
//vector<kmeans_data> Bigdata::kmeans(const CSVData &mycsv){
all_data Kmeans::analyze(const CSVData &mycsv){

	//cout << "kmeans start"<<endl;
	vector<Kmeans*> kmeans;//返り値宣言

	//あらかじめこの中にすべてのorderの値を入れておく
	vector<int> order;
	for(int y =0;y < mycsv.get_col();y++){
		order.push_back(y);
	}

	cout << "kmeans conb:"<< conb(mycsv.get_col(),2) <<endl;
	for(int x=0;x<conb(mycsv.get_col(),2);x++){//nC2回

		Kmeans* k = new Kmeans();
		k->set(mycsv.rabel[order[0]], mycsv.rabel[order[1]]);

		for(int y=0;y<mycsv.get_row();y++){//データ数だけ回る
			P pp;
			pp.set(mycsv.csv_data[y*mycsv.get_col()+order[0]], 
					mycsv.csv_data[y*mycsv.get_col()+order[1]]);
			k->p.push_back(pp);
		}
		k->c_vec = k->assign_c(k->p);//クラスタ数割り当て

		gnuplot(k, x);

		kmeans.push_back(k);

		next_combination(order.begin(),order.begin()+2,order.end());
	}
	all_data a;
	a.mykd = kmeans;
	return a;
}

//Rのアソシエーション分析出力結果専用の行数カウント関数
int Aso::get_col(ifstream &ifs){

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

void Aso::to_var(ifstream &ifs){
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

//vector<aso_data> Bigdata::aso(const CSVData &mycsv){
all_data Aso::analyze(const CSVData &mycsv){
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

	vector<Aso*> aso;//返り値宣言
	Aso *a = new Aso();

	ifstream ifs("all/association/foo.txt");

	//ifs行数取得	
	int col = 0;
	col = a->get_col(ifs);
	cout << col<<endl;
	ifs.clear();
	ifs.seekg(0,ios_base::beg);

	//1行目スキップ
	string line, st;
	getline(ifs,line);

	//2行目以降
	for(int i = 0; i < col; i++){
		a->to_var(ifs);
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
	all_data all;
	all.myad = aso;
	return all;
}

void Kmeans::gnuplot(const Kmeans *k, const int &sheet_num) const
{
	//結果の出力(gnuplot用)
	stringstream output_name;
	output_name << "all/k-means/output/out" << sheet_num << ".txt";

	//クラスタごとに座標をファイルに書き込み
	ofstream fout;
	fout.open(output_name.str());

	for(int i=0; i<K; i++){
		for(int j=0; j < k->p.size(); j++){
			if(k->p[j].get_cluster()==i){
				fout << k->p[j].get_x() << " " << k->p[j].get_y() << endl;
			}
		}
		fout << endl << endl; //次のクラスタ
	}
	fout.close();

	FILE* gnuplot = popen("gnuplot", "w");
	fprintf(gnuplot, "set term png\n");	fprintf(gnuplot, "set output \"all/k-means/graph/result%02d.png\"\n",sheet_num);
	fprintf(gnuplot, "set xl \"%s\"\n", k->get_rab_x().c_str());
	fprintf(gnuplot, "set yl \"%s\"\n", k->get_rab_y().c_str());
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


