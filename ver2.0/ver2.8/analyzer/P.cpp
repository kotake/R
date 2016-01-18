#include "P.hpp"

void P::set(double vx,double vy, int vc){
	x = vx;
	y = vy;
	cluster = vc;
}

//������v�Ƃ̋���
double P::dist(const P v){
	return sqrt((x-v.x)*(x-v.x) + (y-v.y)*(y-v.y));
}
