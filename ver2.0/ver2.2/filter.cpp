#include "head.hpp"

vector<ofstream*> filter(string st_name, double r, string sort_name, int data_num){

	vector<ofstream*> ofs;

	for(int i = 0; i < data_num; i++){
		ofstream fn;
		
		if(st_name == "ALL"){
			
		}
		else if(st_name == "kmeans"){
			
		}
		else if(st_name == "association"){
		
		}
		else if(correlation == "correlation"){
		
		}
		else{cout << "st_nameが間違っています" <<endl:}
		
		ofs.push_back(&fn);
	}
	return ofs;
}
