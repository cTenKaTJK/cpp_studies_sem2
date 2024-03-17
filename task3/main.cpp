#include<iostream>
#include<cstring>
#include"class.hpp"


int main() {
	st::String s1 = "aba";
	st::String s2 = "cd";
	st::String s3, s4;

	std::cin >> s3;

	s4 = s1 + s3 + s2;

	std::cout << s4 << '\n';

	std::cout << s4.find('s') << '\n';

	std::cout << (s1 > s3) << '\n';

	std::cout << s4[3] << '\n';

	s4.at(3, '7');

	std::cout << s4.at(3) << '\n';

	std::cout << s4 << '\n';

	return 0;
}