#include "Fil_kmeans.hpp"
/**
*
*ケーミーンズのフィルター
*/

all_data Fil_kmeans::filtering(all_data *data){
	all_data kara;
	kara.mykd = data->mykd;//(*data).mykdとも書ける
	*data = kara;
	//data->method();的な感じで書く。	
	return *data;
}