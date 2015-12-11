#include "head.hpp"

void fil_kmeans(all_data data){
	all_data kara;

	kara.mykd = data.mykd;

	data = kara;
}

void fil_r(all_data data){

	

}

void write(all_data data){
	if(mkdir("after_fil",777)==0)
		cout << "フォルダafter_filを作成しました"<<endl;

	if(data.mysd.size()!=0){
		//ファイルポインタ獲得
		ofstream ofs("after_fil/sokan_data.txt");
		//for(int i = 0; i < data.mysd.r.size(); i++)
		//	ofs << data.mysd.r[i] << endl;
		ofs.close();
	}
	if(data.mykd.size()!=0){
		//ファイルポインタ獲得
		ofstream ofs("after_fil/kmeans_data.txt");
		//for(int i = 0; i < data.mykd.x.size(); i++)
		//	ofs << data.mykd.x[i] << endl;
		ofs.close();
	}
	if(data.myad.size()!=0){
		//ファイルポインタ獲得
		ofstream ofs("after_fil/aso_data.txt");
		/*for(int i = 0; i < data.myad.lhs.size(); i++){
			ofs << data.myad.lhs << " => " << data.myad.rhs << " : "<< data.myad.support[i] <<" "<< data.myad.confidence[i] << " " << data.myad.lift[i]<<endl;
		}*/
		ofs.close();
	}
}
