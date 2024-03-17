#pragma once


namespace mtr {

	class Matrix {

		int rows_, cols_;
		int** matr_;

	public:

		Matrix(int rows_, int cols_, int* values);

		~Matrix();

		Matrix(const Matrix &other);

		void swap(Matrix& other);

		Matrix& operator = (Matrix other) {
			swap(other);
			return *this;
		}

		void get_info();

	};

}
