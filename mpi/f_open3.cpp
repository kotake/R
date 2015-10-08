#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/shared_array.hpp>

const std::string FNAME("test.csv");
const int SKIP_COLUMNS_NUM = 1;
const int SKIP_ROWS_NUM = 1;
const int ROWS_NUM = 1;

	template <typename T_n>
int readCSV(std::string file_name, T_n &avec)
{
	boost::char_separator<char> sep(",", "", boost::keep_empty_tokens);
	std::ifstream ifs(file_name.c_str());
	std::string line;

	for(int i=0;i<SKIP_COLUMNS_NUM;i++){
		getline(ifs, line);
	}

	while(ifs.good()){
		getline(ifs, line);

		if(line.empty()) break;

		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		tokenizer tokens(line, sep);

		boost::shared_array<double> data(new double[ROWS_NUM]);
		tokenizer::iterator it = tokens.begin();

		for(int i=0;i<SKIP_ROWS_NUM;i++,++it);

		for(int i=0;i<ROWS_NUM;i++,++it){
			std::stringstream ss;
			double d;
			ss << *it;
			ss >> d;
			data[i] = d;
		}
		avec.push_back(data);
	}
	return avec.size();
}

int main(int argc, char* argv[])
{
	typedef std::vector<boost::shared_array<double> > ArrayVector;
	ArrayVector csv_data;

	readCSV(FNAME, csv_data);	

	ArrayVector::iterator it = csv_data.begin();
	for(;it != csv_data.end();++it){
		std::cout << (*it)[0] << ", " << (*it)[1] << ", " << (*it)[2] << std::endl;
	}

	return 0;
}
