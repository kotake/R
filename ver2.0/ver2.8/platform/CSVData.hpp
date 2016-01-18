#ifdef HEADER_H
#define HEADER_H

class CSVData{//csvƒtƒ@ƒCƒ‹‚Ì“ü—Í”
	private:
		int index;
		int col_num;
		int row_num;
	public:
		vector<double> csv_data;
		vector<string> rabel;
		void save_to(string filename);
		void load_from(string filename);
		int get_col() const{return col_num;};
		int get_row() const{return row_num;};
		int get_index() const{return index;};
};

#endif
