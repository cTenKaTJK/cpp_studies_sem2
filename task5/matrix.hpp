#pragma once


namespace mtr {

	template<typename T, size_t R, size_t C>
	class Matrix {

		T matr_[R][C];

	public:

		Matrix() {
			for (size_t i = 0; i < R; i++) {
				for (size_t j = 0; j < C; j++)
					matr_[i][j] = 0;
			}
		}

		~Matrix() {}

		T& operator() (size_t i, size_t j) {
			return matr_[i][j];
		}

		Matrix(Matrix& other) {
			for (size_t i = 0; i < R; i++) {
				for (size_t j = 0; j < C; j++)
					matr_[i][j] = other(i, j);
			}
		}

		Matrix& operator= (Matrix& other) {
			for (size_t i = 0; i < R; i++) {
				for (size_t j = 0; j < C; j++)
					matr_[i][j] = other(i, j);
			}
			return *this;
		}

		Matrix& operator+= (Matrix& other) {
			for (size_t i = 0; i < R; i++) {
				for (size_t j = 0; j < C; j++)
					matr_[i][j] += other(i, j);
			}
			return *this;
		}

		Matrix& operator+ (Matrix& other) {
			Matrix tmp = *this;
			tmp += other;
			return tmp;
		}
		Matrix& operator*= (T& item) {
			for (size_t i = 0; i < R; i++) {
				for (size_t j = 0; j < C; j++)
					matr_[i][j] *= item;
			}
			return *this;
		}
		
		Matrix& operator* (T& item) {
			Matrix tmp = *this;
			tmp *= item;
			return tmp;
		}

		template<size_t other_C>
		Matrix<T, R, other_C>& operator* (Matrix<T, C, other_C>& other) {
			Matrix<T, R, other_C> ans;
			for (size_t row = 0; row < R; row++) {
				for (size_t sec_col = 0; sec_col < other_C; sec_col++) {
					T cell_val = 0;
					for (size_t col = 0; col < C; col++)
						cell_val += matr_[row][col] * other(col, sec_col);
					ans(row, sec_col) = cell_val;
				}
			}
			return ans;
		}

		template<size_t other_C>
		Matrix<T, R, other_C>& operator*= (Matrix<T, C, other_C>& other) {
			//code
		}

		void operator++ ();

	};

	template<typename T, size_t R, size_t C>
	std::ostream& operator<<(std::ostream& out, Matrix<T, R, C>& item) {
		for (size_t i = 0; i < R; ++i) {
			for (size_t j = 0; j < C; ++j) {
				out << item(i, j) << '\t';
			}
			out << '\n';
		}
		out << "--------------------\n";
		return out;
	}

	template<typename T, size_t R, size_t C>
	std::istream& operator>>(std::istream& in, Matrix<T, R, C>& item) {
		for (size_t i = 0; i < R; i++) {
			for (size_t j = 0; j < C; ++j) {
				std::cout << "input item, located on " << i + 1 << " row and " << j + 1 << " column:	";
				in >> item(i, j);
			}
		}
		std::cout << '\n';
		return in;
	}

	template<typename T, size_t R, size_t C>
	void Matrix<T, R, C>::operator++ () {
		for (size_t i = 0; i < R; i++) {
			for (size_t j = 0; j < C; j++)
				++matr_[i][j];
		}
	}

}