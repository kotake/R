#include "../main/main.hpp"

/**
*
*ケーミーンズの分散をしきい値でフィルタリングする
*/

class Fil_r : public Filter{
	public:
		all_data filtering(all_data *data);
};
