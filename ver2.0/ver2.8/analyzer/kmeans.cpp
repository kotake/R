#include "kmeans.hpp"
void Kmeans::set(string r_x, string r_y){
	rab_x = r_x;
	rab_y = r_y;
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

