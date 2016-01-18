//前方宣言
class all_data;

//分析クラス
class Analyzer{//純粋仮想関数を書く
	public:
		Analyzer() {}
		virtual all_data analyze(const CSVData &mycsv) = 0;
		//vector<Kmeans> kmeans(const CSVData &mycsv);
		//void gnuplot (const Kmeans &k, const int &sheet_num) const;
		//vector<Sokan> sokan(const CSVData &mycsv);
		//vector<Aso> aso(const CSVData &mycsv);
		void into_r(double a){r.push_back(a);};//相関係数

	private:
		string line,value;
		vector<double> r;
};
