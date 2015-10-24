#include <iostream>
#include <vector>
#include <algorithm>
#include "next_permutation.hpp"

class P{
	public:
		int x,y;
		P(int a, int b){x = a ; y=b; };
};

int main(){
	const int n = 5, r = 3;
	//std::vector<P> data;
	std::vector<int> data;
	// [0, 1, 2, ....]というサイズnの配列を作成
	for(int i=0; i<n; ++i){
		//data.push_back(P(i,i+1));
		data.push_back(i+1);
		std::cout << "data["<<i<<"]:" << data[i] << std::endl;
	}
	// 全ての組み合わせを出力
	do{
		std::cout << "[ " << data[0];
		for(unsigned int i=1; i<r; ++i){
			std::cout << ", " << data[i];
		}
		std::cout << " ]" << std::endl;
	}while(next_combination(data.begin(), data.begin()+r, data.end()));

	std::cout << "--------------------------" << std::endl;

	for(;next_combination(data.begin(), data.begin()+r, data.end());)
	{
		std::cout << "[ " << data[0];
		for(unsigned int i=1; i<r; ++i){
			std::cout << ", " << data[i];
		}
		std::cout << " ]" << std::endl;
	std::cout<<"data[0]:"<<data[0];
	std::cout<<",data[1]:"<<data[1];
	std::cout<<",data[2]:"<<data[2];
	std::cout<<",data[3]:"<<data[3];
	std::cout<<",data[4]:"<<data[4]<<std::endl;
	}

	//std::cout<<data.begin()<<std::endl;
	return 0;
}
