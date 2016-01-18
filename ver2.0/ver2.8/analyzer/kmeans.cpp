#include "kmeans.hpp"
void Kmeans::set(string r_x, string r_y){
	rab_x = r_x;
	rab_y = r_y;
}

vector<P> Kmeans::assign_c(vector<P> &p){

	//Kmeans�ɂ��N���X�^�����O
	vector<int> prev_cluster, cluster; //�e�_�̃N���X�^�ԍ�

	for(int i=0; i<p.size(); i++){
		prev_cluster.push_back(0);
		cluster.push_back(-1);
	}

	random_device rnd;     // �񌈒�I�ȗ���������
	mt19937 mt(rnd());            // �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h
	//�N���X�^�̏����l����̓f�[�^���烉���_���Ɍ���
	for (int i = 0; i < K; ++i) {
		int rand = mt() % p.size();

		c_vec.push_back(p[rand]);
	}

	//�ʒu���ς��Ȃ��܂�
	while(!isEqual(prev_cluster, cluster)){
		prev_cluster = cluster;

		//���̓x�N�g���̕���
		for(int i=0; i<p.size(); i++){
			int argmax_cluster = -1;
			double argmax_value = INF;
			//��ԗގ��x�̍���(��������ԋ߂�)�N���X�^�ɂ���
			for(int j=0; j<K; j++){
				if(argmax_value > p[i].dist(c_vec[j])){
					argmax_value = p[i].dist(c_vec[j]);
					argmax_cluster = j;
				}
			}
			cluster[i] = argmax_cluster;
			p[i].c_update(cluster[i]);
		}

		//��\�x�N�g���̍Čv�Z
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



//�G���g���|�C���g
//vector<kmeans_data> Bigdata::kmeans(const CSVData &mycsv){
all_data Kmeans::analyze(const CSVData &mycsv){

	//cout << "kmeans start"<<endl;
	vector<Kmeans*> kmeans;//�Ԃ�l�錾

	//���炩���߂��̒��ɂ��ׂĂ�order�̒l�����Ă���
	vector<int> order;
	for(int y =0;y < mycsv.get_col();y++){
		order.push_back(y);
	}

	cout << "kmeans conb:"<< conb(mycsv.get_col(),2) <<endl;
	for(int x=0;x<conb(mycsv.get_col(),2);x++){//nC2��

		Kmeans* k = new Kmeans();
		k->set(mycsv.rabel[order[0]], mycsv.rabel[order[1]]);

		for(int y=0;y<mycsv.get_row();y++){//�f�[�^���������
			P pp;
			pp.set(mycsv.csv_data[y*mycsv.get_col()+order[0]], 
					mycsv.csv_data[y*mycsv.get_col()+order[1]]);
			k->p.push_back(pp);
		}
		k->c_vec = k->assign_c(k->p);//�N���X�^�����蓖��

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
	//���ʂ̏o��(gnuplot�p)
	stringstream output_name;
	output_name << "all/k-means/output/out" << sheet_num << ".txt";

	//�N���X�^���Ƃɍ��W���t�@�C���ɏ�������
	ofstream fout;
	fout.open(output_name.str());

	for(int i=0; i<K; i++){
		for(int j=0; j < k->p.size(); j++){
			if(k->p[j].get_cluster()==i){
				fout << k->p[j].get_x() << " " << k->p[j].get_y() << endl;
			}
		}
		fout << endl << endl; //���̃N���X�^
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
	fflush(gnuplot); //�o�b�t�@�������o��
	pclose(gnuplot);
}

