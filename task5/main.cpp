#include<iostream>

namespace mt {

	template <typename T, size_t ROWS, size_t COLS>
	class Matrix {

	private:
		T** matr_;

	public:

		Matrix() {
			matr_ = new T * [ROWS];
			for (size_t i = 0; i < ROWS; i++) {
				matr_[i] = new T[COLS];
				for (size_t j = 0; j < COLS; j++)
					matr_[i][j] = T(0);
			}
		}

		Matrix(const Matrix& other) {
			for (size_t i = 0; i < ROWS; i++) {
				for (size_t j = 0; j < COLS; j++)
					matr_[i][j] = other.matr_[i][j];
			}
		}

		Matrix& operator=(const Matrix& other) {
			for (size_t i = 0; i < ROWS; i++) {
				for (size_t j = 0; j < COLS; j++)
					matr_[i][j] = other.matr_[i][j];
			}
			return *this;
		}

		~Matrix() {
			for (size_t i = 0; i < ROWS; i++)
				delete[] matr_[i];
			delete[] matr_;
		}

		void operator++(int) {
			for (size_t i = 0; i < ROWS; i++) {
				for (size_t j = 0; j < COLS; j++)
					matr_[i][j]++;
			}
		}

		T& operator() (size_t i, size_t j) {
			return matr_[i][j];
		}

		T* operator[] (size_t i) {
			return matr_[i];
		}

		void Print() {
			for (size_t i = 0; i < ROWS; i++) {
				for (size_t j = 0; j < COLS; j++)
					std::cout << matr_[i][j] << ' ';
				std::cout << '\n';
			}
		}

	};

	template<typename T, size_t ROWS, size_t COLS>
	std::ostream& operator<< (std::ostream& out, const Matrix<T, ROWS, COLS>& item) {
		for (size_t i = 0; i < ROWS; i++) {
			for (size_t j = 0; j < COLS; j++)
				out << item(i, j) << ' ';
			out << '\n';
		}
		return out;
	}

}


int main() {
	mt::Matrix<float, 3, 3> m;
	std::cout << m;
	m(1, 2) = 1.25f;
	m[1][0] = 6.21f;
	m++;
	std::cout << m;
	mt::Matrix<float, 3, 3> m1 = m;
	std::cout << m1;

	return 0;
}