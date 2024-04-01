#include<iostream>
#include"matrix.hpp"


int main() {

	mtr::Matrix<int, 2, 2> a;
	mtr::Matrix<int, 2, 2> b;

	std::cin >> a;
	std::cin >> b;

	std::cout << "initial matrixes\n" << a << b;

	a *= -1;
	b *= 2;

	std::cout << "new matrixres\n" << a << b;

	std::cout << "1`st matrix det\n" << a.det() << std::endl;
	std::cout << "2`nd matrix det\n" << b.det() << "\n--------------------" << std::endl;

	std::cout << "addition result\n" << a + b;
	std::cout << "multiplication result\n" << a * b;


	return 0;

}