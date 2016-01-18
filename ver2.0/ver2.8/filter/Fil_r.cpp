#include "Fil_r.hpp"

/**
*
*�P�[�~�[���Y�̕��U���������l�Ńt�B���^�����O����
*/
all_data Fil_r::filtering(all_data *data){
	//kmeans	
	//�N���X�^���Ƃ̕W���΍����v�Z
	cout << "mysd.size():"<< data -> mysd.size() << endl;
	cout << "mykd.size():"<< data -> mykd.size() << endl;
	cout << "myad.size():"<< data -> myad.size() << endl;

	//�d�v�I
	vector<Kmeans*> a = data->mykd;
	cout << "a.size():"<< a.size() <<endl;

	int it =0,rem_num=0;
	//kmeans
	//for(int i=0;i < a.size() ;i++){//nC2
	for(int i = a.size()-1;i!=0;i--){
		for(int j=0;j<K;j++){//�N���X�^��
			double sum = 0, avg = 0, tmp = 0;
			int count = 0;
			for(int k=0;k<a[0]->p.size();k++){//�f�[�^��
				//�N���X�^��k�̕��ς��o������
				if(a[i]->p[k].get_cluster()==j){
					sum += a[i]->p[k].dist(a[i]->c_vec[j]);
					count++;//���N���X�^�Ɋ܂܂��f�[�^��
				}
			}
			avg = sum / (double)count;
			for(int k=0;k<a[0]->p.size();k++){
				double hensa = a[i]->p[k].dist(a[i]->c_vec[j]) - avg;
				tmp += hensa * hensa;
			}
			//�e�N���X�^�̕W���΍����v�Z
			double SD, SD_max = 0, SD_min = INT_MAX;
			SD = sqrt(tmp / (double)count);
			//if(SD_max < SD) SD_max = SD;
			//if(SD_min > SD) SD_min = SD;
			cout << "�폜�O�V�[�g"<<i <<" "<<"�N���X�^"<< j <<"�̕W���΍��F"<< SD <<endl;

			//��������t�B���^�[
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
	cout << "�폜�������F"<<rem_num<<endl;
	cout << "mykd.size():"<< data -> mykd.size() <<endl;

	return *data;
}

/*
void s_sort(vector<double> key, vector<sokan_data> *sd){
	
	if(key.size()!=sd->size())
		cout << "�T�C�Y����v���Ă��܂���"<<endl;

	for(int i=0;i<sd->size();i++){
		map<SD,data->mykd[i]>//�L�[�A�o�����[�̏�
	}
}*/

