#include "Analyzer.hpp"
#include "Filter.hpp"

//#include "CSVData.cpp"

//#include "../analyzer/Aso.cpp"
//#include "../analyzer/kmeans.cpp"
//#include "../analyzer/Sokan.cpp"

#include "All_data.hpp"
//�v���b�g�t�H�[���N���X
class Platform{
	public:
		//Platform()=default;
		void addAnalyzer(Analyzer *a);
		void addFilter(Filter *a);
		void input(string filename);
		void execute();
		void output();
	private:
		list<Analyzer*> analyzer_list;
		list<Filter*> filter_list;
		all_data d;
		CSVData csv;
		//vector<Sokan> mysd;
		//vector<Kmeans> mykd;
		//vector<Aso> myad;
		//������method()�������B
		void method1();
		void method2();
};

