
//all_data�N���X�̓���N���X
class Aso : public Analyzer{//�킩��Ȃ���
	public:
		all_data analyze(const CSVData &mycsv);
		void to_var(ifstream &ifs);
		int get_col(ifstream &ifs);
		string get_lhs() const{return lhs;};
		string get_rhs() const{return rhs;};
		double get_support() const{return support;};
		double get_confidence() const{return confidence;};
		double get_lift() const{return lift;};

	private:
		string lhs;
		string rhs;
		double support;
		double confidence;
		double lift;
};
