#include "Sokan.hpp"

void Sokan::set(string r_x, string r_y, double vr){
	rab_x = r_x;
	rab_y = r_y;
	r = vr;
}


all_data Sokan::analyze(const CSVData &mycsv){
	//vector<all_data> Sokan::analyze(const CSVData &mycsv){
	//cout << "sokan start"<<endl;
	vector<int> order;
	vector<P> input;
	input.reserve(mycsv.get_row());
	for(int x = 0; x < mycsv.get_col(); x++){
		order.push_back(x);
	}
	vector<Sokan*> sokan;//•Ô‚è’l‚ÌéŒ¾
	Sokan* s = new Sokan();//‚±‚ês‚ğsokan‚ÉnC2‰ñpush_back‚·‚é

	stringstream output_name;
	output_name << "all/correlation/output.txt";
	ofstream sokanf;
	sokanf.open(output_name.str());
	cout << "sokan conb:"<< conb(mycsv.get_col(),2) <<endl;

	for(int x = 0; x < conb(mycsv.get_col(),2); x++){
		sokanf << "[ " << order[0]<<"—ñ–Ú‚Æ"<<order[1]<<"—ñ–Ú ]"<<endl;
		for(int y=0 ;y < mycsv.get_col() ;y++){
			input[y].set(mycsv.csv_data[y * mycsv.get_col() + order[0]],
					mycsv.csv_data[y * mycsv.get_col() + order[1]]);
		}

		double r=0;
		double x_avg=0,y_avg=0;
		double chi=0,mo1=0,mo2=0;
		vector<double> tmp_x,tmp_y;
		for(int i=0; i < mycsv.get_row(); i++){
			tmp_x.push_back(input[i].get_x());
		}
		x_avg = accumulate(tmp_x.begin(), tmp_x.end(), 0.0)/(double)mycsv.get_row();
		for(int i=0;i<mycsv.get_row();i++){
			tmp_y.push_back(input[i].get_y());
		}
		y_avg = accumulate(tmp_y.begin(),tmp_y.end(),0.0)/(double)mycsv.get_row();

		for(int i =0;i < mycsv.get_row();i++){
			chi += (input[i].get_x() - x_avg) * (input[i].get_y() - y_avg);
			mo1 += pow((input[i].get_x() - x_avg),2.0);
			mo2 += pow((input[i].get_y() - y_avg),2.0);
		}
		r = chi / (sqrt(mo1)*sqrt(mo2));
		sokanf <<"‘ŠŠÖŒW”:"<< r << endl << endl;
		s->set(mycsv.rabel[order[0]], mycsv.rabel[order[1]], r);
		sokan.push_back(s);

		next_combination(order.begin(),order.begin()+2,order.end());
	}

	sokanf.close();

	all_data a;
	a.mysd = sokan;
	return a;
}
