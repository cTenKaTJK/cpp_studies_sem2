#include<iostream>
#include"matrix.hpp"


//	�������� *= �� ������� � �����, ��������� ������ � ������� ����������� �������� � ����������� ������������
int main() {
	mtr::Matrix<int, 3, 2> a;
	std::cin >> a;
	mtr::Matrix<int, 2, 3> b;
	std::cin >> b;
	std::cout << a;
	std::cout << b;
	mtr::Matrix<int, 3, 3> c = a * b;
	std::cout << c;
	return 0;
}