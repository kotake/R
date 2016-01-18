#include "Platform.hpp"

//���̊֐���3�̓��v�������s��
void Platform::execute(){

	//Bigdata mybd;
	all_data tmp;

	//mysd = mybd.sokan(data);//mydata�̒���mysd�ɃA�N�Z�X
	//mykd = mybd.kmeans(data);//mydata�̒���mykd�ɃA�N�Z�X
	//myad = mybd.aso(data);//all_data::aso_data

	list<Analyzer*>::iterator it_a = analyzer_list.begin();
	for(int i=0;it_a!=analyzer_list.end();it_a++,i++){
		tmp = (*it_a)->analyze(csv);//�eall_data���qall_data
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


void Platform::addAnalyzer(Analyzer *a){
	analyzer_list.push_back(a);
}

void Platform::addFilter(Filter *a){
	filter_list.push_back(a);
}

void Platform::input(string filename){
	csv.load_from(filename);
}

void Platform::output(){

}
