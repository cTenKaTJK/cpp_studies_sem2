#include<iostream>
#include"MyLongInt.hpp"


int main() {
	lt::MyLongInt a("-1001");
	lt::MyLongInt b = "296";
	lt::MyLongInt c, d;
	std::cin >> b;
	std::cout << a << ' ' << b << '\n';
	c = a + b;
	d = a * b;
	std::cout << c << ' ' << d << '\n';
	return 0;
}