#include "P.cpp"
//all_data�N���X�̓���N���X
class Kmeans : public Analyzer{//nC2��
	public:
		all_data analyze(const CSVData &mycsv);
		void set(string r_x, string r_y);
		//P set(P vp, int cluster);
		vector<P> assign_c(vector<P> &p);
		void gnuplot (const Kmeans *k, const int &sheet_num) const;
		string get_rab_x() const{return rab_x;};
		string get_rab_y() const{return rab_y;};
		vector<P> c_vec;//K��
		vector<P> p;//�S��������Ȃ���
	private:
		string rab_x;
		string rab_y;
};
