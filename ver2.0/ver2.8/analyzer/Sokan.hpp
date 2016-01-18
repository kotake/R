//all_dataクラスの内包クラス
class Sokan : public Analyzer{//nC2個
	public:
		all_data analyze(const CSVData &mycsv);
		void set(string r_x, string r_y, double vr);
		string get_rab_x()const{return rab_x;};
		string get_rab_y()const{return rab_y;};
		double get_r()const{return r;};
	private:
		string rab_x;
		string rab_y;
		double r;
	public:
		bool operator< (const Sokan& right) const{
			return r == right.r ? rab_x > right.rab_x : r > right.r;
		}
};
