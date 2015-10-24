#include <iostream>
#include <vector>
#include <algorithm>

int main(){
	const int n = 3;
	std::vector<int> data;
	// [0, 1, 2, ....]というサイズnの配列を作成
	for(int i=0; i<n; ++i){
		data.push_back(i);
	}
	// 全ての順列を出力
	do{
		std::cout << "[ " << data[0];
		for(unsigned int i=1; i<data.size(); ++i){
			std::cout << ", " << data[i];
		}
		std::cout << " ]" << std::endl;
	}while(next_permutation(data.begin(), data.end()));

	return 0;
}
