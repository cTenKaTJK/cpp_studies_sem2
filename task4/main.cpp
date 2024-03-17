#include<iostream>
#include"MyLongInt.hpp"


int main() {
	lt::MyLongInt a, b;
	std::cin >> a >> b;
	std::cout << "a:    " << a << "     b:    " << b << "\na == b:    " << (a == b) << "\na != b:    " << (a != b) << "\na < b:    " << (a < b) << "\na * b:    " << (a * b) << "\na + b:    " << (a + b) << '\n';
	return 0;
}
