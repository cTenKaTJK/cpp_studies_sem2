#include<iostream>
#include"class.hpp"


int main() {

	int n;
	std::cout << "input tetrs count:    ";
	std::cin >> n;

	for (int i = 0; i < n; i++) {

		float edge;

		std::cout << "-----------------\n";

		std::cout << "input tetr edges lengh:    ";
		std::cin >> edge;

		mtetr::Tetr t(edge);

		std::cout << "Tetrahedron edges length is:    " << t.get_edge() << std::endl;
		std::cout << "Tetrahedron square is:    " << t.get_square() << std::endl;
		std::cout << "Tetrahedron volume length is:    " << t.get_volume() << std::endl;

	}
	std::cout << "-----------------\n";
	return 0;
}