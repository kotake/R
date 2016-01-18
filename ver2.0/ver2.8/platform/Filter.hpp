//フィルタークラス
class Filter{//純粋仮想関数を書く
	public:
		Filter() {}
		virtual all_data filtering(all_data *data) = 0;
};
