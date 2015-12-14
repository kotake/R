//このファイルは、ユーザーは記述するファイルです
//filter関数内でファイル書き込み禁止

#include "head.hpp"
#include"check.hpp"

void fil_kmeans(all_data *data){

	all_data kara;

	kara.mykd = data->mykd;//(*data).mykdとも書ける

	*data = kara;
}

void fil_r(all_data *data){
/*	//kmeans	
	//クラスタごとの標準偏差を計算
	double SD[K];
	for(int i=0;i<K;i++){
		SD[i] = 0
	}
	for(int i = 0; i < K; i++){
		double avg = 0,tmp = 0;
		int count = 0;
		for(int j = 0; j < mycsv.get_row(); j++){
			if(cluster[j]==i){
				tmp += P::dist(input[j], vec_m[i]);
				count++;
			}
		} 
		avg = tmp / (double)count;
		tmp = 0;
		for(int j = 0; j < mycsv.get_row(); j++){
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
	*/
}

