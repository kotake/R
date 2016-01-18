#include "Fil_r.hpp"

/**
*
*ケーミーンズの分散をしきい値でフィルタリングする
*/
all_data Fil_r::filtering(all_data *data){
	//kmeans	
	//クラスタごとの標準偏差を計算
	cout << "mysd.size():"<< data -> mysd.size() << endl;
	cout << "mykd.size():"<< data -> mykd.size() << endl;
	cout << "myad.size():"<< data -> myad.size() << endl;

	//重要！
	vector<Kmeans*> a = data->mykd;
	cout << "a.size():"<< a.size() <<endl;

	int it =0,rem_num=0;
	//kmeans
	//for(int i=0;i < a.size() ;i++){//nC2
	for(int i = a.size()-1;i!=0;i--){
		for(int j=0;j<K;j++){//クラスタ数
			double sum = 0, avg = 0, tmp = 0;
			int count = 0;
			for(int k=0;k<a[0]->p.size();k++){//データ数
				//クラスタ数kの平均を出したい
				if(a[i]->p[k].get_cluster()==j){
					sum += a[i]->p[k].dist(a[i]->c_vec[j]);
					count++;//同クラスタに含まれるデータ数
				}
			}
			avg = sum / (double)count;
			for(int k=0;k<a[0]->p.size();k++){
				double hensa = a[i]->p[k].dist(a[i]->c_vec[j]) - avg;
				tmp += hensa * hensa;
			}
			//各クラスタの標準偏差を計算
			double SD, SD_max = 0, SD_min = INT_MAX;
			SD = sqrt(tmp / (double)count);
			//if(SD_max < SD) SD_max = SD;
			//if(SD_min > SD) SD_min = SD;
			cout << "削除前シート"<<i <<" "<<"クラスタ"<< j <<"の標準偏差："<< SD <<endl;

			//ここからフィルター
			if(SD>1.0){
				//data -> mykd.erase(data->mykd.begin() + it);
				data -> mykd.erase(data->mykd.begin()+i);
				it--;
				rem_num++;
				break;
			}
			it++;
		}
		cout << endl;
	}
	cout << "削除した数："<<rem_num<<endl;
	cout << "mykd.size():"<< data -> mykd.size() <<endl;

	return *data;
}

/*
void s_sort(vector<double> key, vector<sokan_data> *sd){
	
	if(key.size()!=sd->size())
		cout << "サイズが一致していません"<<endl;

	for(int i=0;i<sd->size();i++){
		map<SD,data->mykd[i]>//キー、バリューの順
	}
}*/

