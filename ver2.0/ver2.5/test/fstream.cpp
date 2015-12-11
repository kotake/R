#include <iostream>
#include <fstream>

std::ifstream open_config_file()
{
	std::ifstream s("app.conf");
	s.exceptions(std::ios_base::badbit | std::ios_base::failbit);
	// return std::move(s);でも可
	return s;
}

int main()
{
	auto f = open_config_file();
	// ここでfから読み込む処理。
}
