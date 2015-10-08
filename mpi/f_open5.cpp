#include <fstream>
#include <string>

#include <boost/timer.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/container.hpp>
#include <boost/spirit/include/phoenix_core.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

/*	template <typename Iterator>
bool parse_csv(Iterator first, Iterator last, std::vector<int>& vec)
{
	using qi::int_;
	using qi::phrase_parse;
	using qi::_1;
	using ascii::space;
	using phoenix::push_back;

	bool r = phrase_parse(first, last,
			// Begin grammar
			(
			 int_[push_back(phoenix::ref(vec), _1)] % ','
			)
			,
			// End grammar
			space);

	if (first != last)
		return false;
	return r;
}
*/

bool read_csv_getline(const char* filename, unsigned short* buf)
{
	std::ifstream ifs(filename);

	std::string line;
	unsigned int index = 0;
	while (std::getline(ifs, line)) {
		std::stringstream ss(line);
		std::string value;
		while (std::getline(ss, value, ',')) {
			buf[index] = atoi(value.c_str());
			index++;
		}
	}
	
	for(int i=0;i<30;i++){
		std::cout << buf[i] <<std::endl;
	}
	return true;
}

/*
bool read_csv_spirit(const char* filename, unsigned short* buf)
{
	std::ifstream ifs(filename);

	std::string line;
	unsigned int index = 0;
	while (std::getline(ifs, line)) {
		std::vector<int> read_buf;
		if (parse_csv(line.begin(), line.end(), read_buf)) {
			for (int i = 0; i < read_buf.size(); i++) {
				buf[index] = read_buf[i];
				index++;
			}
		} else {
			return false;
		}
	}
	return true;
}*/

int main() {

	unsigned short* buf = new unsigned short[28829184];

	//boost::timer t1;
	read_csv_getline("test.csv", buf);
	//std::cout << t1.elapsed() << std::endl;

	/*boost::timer t2;
	read_csv_spirit("test.csv", buf);
	std::cout << t2.elapsed() << std::endl;
*/
	delete[] buf;

	return 0;
}
