//all_dataクラスが内包するkmeans_dataクラスの内包クラス
class P{
	public:
		void set(double vx, double vy, int vc=-1);
		//P set(double x,double y);
		void c_update(int new_c){cluster = new_c;};
		double dist(P v);
		double get_x()const{return x;};
		double get_y()const{return y;};
		int get_cluster()const{return cluster;};
	private:
		double x;
		double y;
		int cluster;
		//static double dist(P a, P b);
};
