#include<iostream>
#include"class.hpp"


int main() {

	int n = 3, m = 2;
	int vals[]{1, 2, 3, 4, 5, 6};
	int vals_2[]{ 1, 2, 4, 4, 5, 6 };

	mtr::Matrix m1(n, m, vals);
	mtr::Matrix m2(n, m, vals_2);
	mtr::Matrix m3 = m1;
	

	m1.get_info();
	m2 = m1;
	m2.get_info();
	m3.get_info();

	return 0;
}
