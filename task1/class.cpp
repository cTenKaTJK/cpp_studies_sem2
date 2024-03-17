#include<iostream>
#include<cmath>
#include"class.hpp"


namespace mtetr {

	Tetr::Tetr(float edge) {
		Tetr::edge_ = edge;
		std::cout << "Tetrahedron sucessfuly consructed!" << std::endl;
	}

	Tetr::~Tetr() {
		std::cout << "Tetrahedron sucessfuly destructed!" << std::endl;
	}

	float Tetr::get_edge() {
		return edge_;
	}

	float Tetr::get_square() {
		return pow(edge_, 2) * sqrt(3);
	}

	float Tetr::get_volume() {
		return pow(edge_, 3) * sqrt(2) / 12;
	}
}