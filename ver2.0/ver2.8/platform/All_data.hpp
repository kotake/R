//コンポジション
class all_data{
	public:
		all_data();
		//void all(CSVData &data);
		//void set_rabel(CSVData source);
	//private:
		vector<Sokan*> mysd;
		vector<Kmeans*> mykd;
		vector<Aso*> myad;
};


all_data::all_data(){
	mysd.clear();
	mykd.clear();
	myad.clear();
}
