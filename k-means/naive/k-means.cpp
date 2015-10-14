#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

static const double INF = 1000000000.0;

//平面ベクトルデータ
class P{
	public:
	double x, y;
	P(double a,double b){x = a; y = b;};
};

//2点間の距離
double dist(P a, P b){
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

//収束判定(各点が属するクラスタが変化しないかどうか)
bool isEqual(vector<int> a, vector<int> b){
	for(int i=0; i<a.size(); i++){
		if(a[i]!=b[i]) return false;
	}
	return true;
}

//エントリポイント
int main(){

	//入力データ
	vector<P> input;
	double x, y;
	while(cin >> x >> y){
		input.push_back((P){x,y});
	}

	//Kmeansによるクラスタリング
	int K = 3; //クラスタ数
	vector<int> prev_cluster, cluster; //各点のクラスタ番号
	vector<P> vec_m; //各クラスタの代表ベクトル

	for(int i=0; i<input.size(); i++){
		prev_cluster.push_back(0);
		cluster.push_back(-1);
	}
	//検証のため、代表ベクトルの初期位置を手動で決める
	vec_m.push_back(P(2.0,90.0));
	vec_m.push_back(P(5.0,50.0));
	vec_m.push_back(P(3.0,70.0));


	while(!isEqual(prev_cluster, cluster)){
		prev_cluster = cluster;

		//入力ベクトルの分割
		for(int i=0; i<input.size(); i++){
			int argmax_cluster = -1;
			double argmax_value = INF;
			//一番類似度の高い(距離が一番近い)クラスタにする
			for(int j=0; j<K; j++){
				if(argmax_value > dist(input[i], vec_m[j])){
					argmax_value = dist(input[i], vec_m[j]);
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
			for(int j=0; j<input.size(); j++){
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
	for(int i=0; i<K; i++){
		for(int j=0; j<input.size(); j++){
			if(cluster[j]==i){
				cout << input[j].x << " " << input[j].y << endl;
			}
		}
		cout << endl << endl; //次のクラスタ
	}

	return 0;
}
