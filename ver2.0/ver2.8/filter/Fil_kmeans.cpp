#include "Fil_kmeans.hpp"
/**
*
*�P�[�~�[���Y�̃t�B���^�[
*/

all_data Fil_kmeans::filtering(all_data *data){
	all_data kara;
	kara.mykd = data->mykd;//(*data).mykd�Ƃ�������
	*data = kara;
	//data->method();�I�Ȋ����ŏ����B	
	return *data;
}