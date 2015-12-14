#include "head.hpp"

void print(all_data D){
	cout<<endl<< "=========debug_start=============="<<endl<<endl;

	//sokan
	for(int i =0;i < D.mysd.size() ; i++){
		cout << "sokan["<<i<<"]"<<endl;
		cout << "  rabel_x:" << D.mysd[i].rab_x << endl;
		cout << "  rabel_y:" << D.mysd[i].rab_y << endl;
	}
	cout << endl;

	//k-means
	for(int i =0;i < D.mykd.size() ; i++){
		cout << "kmeans["<<i<<"]"<<endl;
		cout << "  rabel_x:" << D.mykd[i].rab_x << endl;
		cout << "  rabel_y:" << D.mykd[i].rab_y << endl;
		for(int j=0;j<D.mykd[i].c_vec.size();j++){
			cout << "    mykd["<<i<<"]:"<<"c_vec["<<j<<"]:";
			cout << "("<<D.mykd[i].c_vec[j].x<<", ";
			cout << D.mykd[i].c_vec[j].y<<", ";
			cout << D.mykd[i].c_vec[j].cluster<<")"<< endl;
		}
		for(int j=0;j<D.mykd[i].p.size();j++){
			cout << "    mykd["<<i<<"]:"<<"pt["<<j<<"]:";
			cout << "("<<D.mykd[i].p[j].x<<", ";
			cout << D.mykd[i].p[j].y<<", ";
			cout << D.mykd[i].p[j].cluster<<")"<< endl;
		}
	}
	

	//aso
	cout << D.myad.size()<< endl;
	for(int i =0;i < D.myad.size() ; i++){
		cout << "aso["<<i<<"]"<<endl;
		cout << "  lhs:" << D.myad[i].lhs << ", ";
		cout << "rhs:" << D.myad[i].rhs << ", ";
		cout << "support:" << D.myad[i].support << ", ";
		cout << "confidence:" << D.myad[i].confidence << ", ";
		cout << "lift:" << D.myad[i].lift << ", ";
		cout << endl;
	}

	cout<<endl<< "=========debug_end=============="<<endl<<endl;

}
