#include<iostream>
#include"ob.hpp"

int main()
{
	DataClass DataA;
	CalcClass CalcA;

	DataA.a=1;
	DataA.b=2;
	DataA.sum=0;

	CalcA.add(DataA);

	std::cout << DataA.sum << std::endl;

	return 0;
}
