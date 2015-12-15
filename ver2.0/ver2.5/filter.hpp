//このファイルは、ユーザーは記述するファイルです
//filter関数内でファイル書き込み禁止を禁止

#include "head.hpp"
#include"check.hpp"

void fil_kmeans(all_data *data){

	all_data kara;

	kara.mykd = data->mykd;//(*data).mykdとも書ける

	*data = kara;
}

void fil_r(all_data *data){
	//kmeans	
	//クラスタごとの標準偏差を計算
	
	cout << "mysd.size():"<< data -> mysd.size() <<endl;
	cout << "mykd.size():"<< data -> mykd.size() <<endl;
	cout << "myad.size():"<< data -> myad.size() <<endl;

	//kmeans
	for(int i=0;i < data->mykd.size() ;i++){//nC2
		for(int j=0;j<K;j++){//クラスタ数
			double sum = 0, avg = 0, tmp = 0;
			int count = 0;
			for(int k=0;k<data->mykd[0].p.size();k++){//データ数
				//クラスタ数kの平均を出したい
				if(data->mykd[i].p[k].get_cluster()==j){
					sum += data->mykd[i].p[k].dist(data->mykd[i].c_vec[j]);
					count++;//同クラスタに含まれるデータ数
				}
			}
			avg = sum / (double)count;
			for(int k=0;k<data->mykd[0].p.size();k++){
				double hensa = data->mykd[i].p[k].dist(data->mykd[i].c_vec[j]) - avg;
				tmp += hensa * hensa;
			}
			//各クラスタの標準偏差を計算
			double SD, SD_max = 0, SD_min = INT_MAX;
			SD = sqrt(tmp / (double)count);
			if(SD_max < SD) SD_max = SD;
			if(SD_min > SD) SD_min = SD;
			cout << "シート"<<i <<" "<<"クラスタ"<< j <<"の標準偏差："<< SD <<endl;
		}
		cout << endl;

	}

	/*	for(int i = 0; i < K; i++){
		double avg = 0, tmp = 0;
		int count = 0;
	//平均を出したい
	for(int j = 0; j < data->mykd[0].p.size(); j++){
	if(data->mykd[j].c_vec[i]==i){
	tmp += data->mykd[i].p[j].dist(vec_m[i]);
	count++;
	}
	} 
	avg = tmp / (double)count;
	tmp = 0;
	for(int j = 0; j < mycsv.get_row(); j++){
	double hensa = p[j].dist(data->mykd[j].c_vec) - avg;
	tmp += hensa * hensa;
	SD[i] = sqrt(tmp / (double)count);
	}
	}
	*/


	/*for(int i = 0; i < K; i++){
		cout << "クラスタ["<<i<<"]の標準偏差:"<< SD[i] << "	現在--->最大値:" << SD_max[i] <<" 最小値:" << SD_min[i] << endl;
	}

	cout << endl;*/
}

