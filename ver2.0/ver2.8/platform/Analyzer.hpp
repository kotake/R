//�O���錾
class all_data;

//���̓N���X
class Analyzer{//�������z�֐�������
	public:
		Analyzer() {}
		virtual all_data analyze(const CSVData &mycsv) = 0;
		//vector<Kmeans> kmeans(const CSVData &mycsv);
		//void gnuplot (const Kmeans &k, const int &sheet_num) const;
		//vector<Sokan> sokan(const CSVData &mycsv);
		//vector<Aso> aso(const CSVData &mycsv);
		void into_r(double a){r.push_back(a);};//���֌W��

	private:
		string line,value;
		vector<double> r;
};
