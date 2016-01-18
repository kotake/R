#include "head.hpp"

void print(const all_data &D){
	cout<<endl<< "=========debug_start=============="<<endl<<endl;

	//sokan
	for(int i =0;i < D.mysd.size() ; i++){
		cout << "sokan["<<i<<"]"<<endl;
		cout << "  rabel_x:" << D.mysd[i]->get_rab_x() << endl;
		cout << "  rabel_y:" << D.mysd[i]->get_rab_y() << endl;
	}
	cout << endl;

	//k-means
	for(int i =0;i < D.mykd.size() ; i++){
		cout << "kmeans["<<i<<"]"<<endl;
		cout << "  rabel_x:" << D.mykd[i]->get_rab_x() << endl;
		cout << "  rabel_y:" << D.mykd[i]->get_rab_y() << endl;
		for(int j=0;j<D.mykd[i]->c_vec.size();j++){
			cout << "    mykd["<<i<<"]:"<<"c_vec["<<j<<"]:";
			cout << "("<<D.mykd[i]->c_vec[j].get_x()<<", ";
			cout << D.mykd[i]->c_vec[j].get_y()<<", ";
			cout << D.mykd[i]->c_vec[j].get_cluster()<<")"<< endl;
		}
		for(int j=0;j<D.mykd[i]->p.size();j++){
			cout << "    mykd["<<i<<"]:"<<"pt["<<j<<"]:";
			cout << "("<<D.mykd[i]->p[j].get_x()<<", ";
			cout << D.mykd[i]->p[j].get_y()<<", ";
			cout << D.mykd[i]->p[j].get_cluster()<<")"<< endl;
		}
	}
	

	//aso
	cout << D.myad.size()<< endl;
	for(int i =0;i < D.myad.size() ; i++){
		cout << "aso["<<i<<"]"<<endl;
		cout << "  lhs:" << D.myad[i]->get_lhs() << ", ";
		cout << "rhs:" << D.myad[i]->get_rhs() << ", ";
		cout << "support:" << D.myad[i]->get_support() << ", ";
		cout << "confidence:" << D.myad[i]->get_confidence() << ", ";
		cout << "lift:" << D.myad[i]->get_lift() << ", ";
		cout << endl;
	}

	cout<<endl<< "=========debug_end=============="<<endl<<endl;

}
