#include<iostream>
#include"class.hpp"


namespace mtr {

	Matrix::Matrix(int n, int m, int* values) {
		Matrix::rows_ = n;
		Matrix::cols_ = m;
		Matrix::matr_ = new int* [n];
		for (int i = 0; i < n; i++) {
			matr_[i] = new int[m];
			for (int j = 0; j < m; j++) {
				matr_[i][j] = values[(i * m) + j];
			}
		}
		std::cout << "-sucessfuly constructed-\n";
	}

	Matrix::~Matrix() {
		std::cout << "-sucessfuly destructed-\n";
	}	

	Matrix::Matrix(const Matrix& other) {
		rows_ = other.rows_;
		cols_ = other.cols_;
		matr_ = other.matr_;
		std::cout << "-sucessfuly copied-\n";
	}

	void Matrix::swap(Matrix &other) {
		std::swap(rows_, other.rows_);
		std::swap(cols_, other.cols_);
		std::swap(matr_, other.matr_);
	}

	void Matrix::get_info() {
		std::cout << "matrix length:    " << cols_;
		std::cout << "\nmatrix width:    " << rows_ << '\n';
		for (int i = 0; i < rows_; i++) {
			for (int j = 0; j < cols_; j++) {
				std::cout << matr_[i][j] << '\t';
			}
		std::cout << '\n';
		}
		std::cout << "------------------\n";
	}

}
