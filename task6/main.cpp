#include<iostream>
#include<bitset>
#include<cstring>
#include<cmath>


namespace vec {

	template<typename T>
	class vector {};

	template<>
	class vector<bool> {

	private:
		char* data_;
		size_t len_;
		size_t cell_;

		// подкласс укзателя на бит в байте
		class bitptr {
		private:
			char* ptr_;
			int move_;

		public:
			bitptr(char* ptr, size_t index, size_t len) {
				ptr_ = ptr;
				move_ = (index >= (len - (len % 8)) ? 7 - (index % 8) - (8 - len % 8) : 7 - index % 8);
			}

			bitptr& operator=(bool b) {
				if (b)
					*ptr_ = *ptr_ | (1 << move_);
				else
					*ptr_ = *ptr_ & ~(1 << move_);
				return *this;
			}

			operator bool() const {
				char mask = 1 << move_;
				return bool(*ptr_ & mask);
			}
		};

	public:
		vector() {
			len_ = 0;
			cell_ = 0;
			data_ = new char[1];
		}

		vector(std::string str) {
			vector vec;
			for (size_t i = 0; i < str.length(); i++) {
				if (str[i] == '0')
					vec.pushback(false);
				else if (str[i] == '1')
					vec.pushback(true);
			}
			*this = vec;
		}

		~vector() { delete[] data_; }

		vector(const vector& other) {
			len_ = other.len_;
			cell_ = other.cell_;
			data_ = new char[cell_ + 1];
			for (size_t i = 0; i < cell_ + 1; i++)
				data_[i] = other.data_[i];
		}

		vector& operator=(vector& other) {
			len_ = other.len_;
			cell_ = other.cell_;
			data_ = new char[cell_ + 1];
			for (size_t i = 0; i < cell_ + 1; i++)
				data_[i] = other.data_[i];
			return *this;
		}

		void pushback(bool value) {
			if (len_ % 8 == 0 && len_ > 0)
				extend();
			else
				data_[cell_] = data_[cell_] << 1;
			data_[cell_] = data_[cell_] | value;
			len_++;
		}

		void extend() {
			cell_++;
			char* tmp = new char[cell_ + 1];
			for (size_t i = 0; i < cell_; i++)
				tmp[i] = data_[i];
			tmp[cell_] = 0;
			data_ = tmp;
		}

		size_t size() {
			return len_;
		}

		bitptr operator[] (size_t index) {
			return bitptr(data_ + index / 8, index, len_);
		}

		const bitptr operator[](size_t index) const {
			return bitptr(data_ + index / 8, index, len_);
		}

		void erase(size_t index) {
			vector tmp = *this;

			if (len_ % 8 == 0 && len_ > 8) {
				for (size_t i = index; i < (8 * cell_); i++) {
					bool blank = tmp[i];
					tmp[i] = bool(tmp[i + 1]);
					tmp[i + 1] = blank;
				}
			}
			else {
				if (cell_ > 0 && (index < (8 * (cell_)))) {
					for (size_t i = index; i < (8 * cell_); i++) {
						bool blank = tmp[i];
						tmp[i] = bool(tmp[i + 1]);
						tmp[i + 1] = blank;
					}
				}

				for (size_t i = index; i > (8 * cell_); i--) {
					bool blank = tmp[i];
					tmp[i] = bool(tmp[i - 1]);
					tmp[i - 1] = blank;
				}
			}
			tmp.len_--;
			*this = tmp;
		}

		void insert(size_t index, bool value) {
			vector tmp = *this;

			tmp.pushback(value);

			for (size_t i = len_; i > index; i--) {
				bool blank = tmp[i];
				tmp[i] = bool(tmp[i - 1]);
				tmp[i - 1] = blank;
			}

			*this = tmp;
		}

		friend std::ostream& operator<<(std::ostream& out, vector<bool>& item);
	};


	std::ostream& operator<<(std::ostream& out, vector<bool>& item) {
		for (size_t i = 0; i < item.size(); i++) {
			if (i % 8 == 0 && i != 0)
				std::cout << '|';
			out << item[i];
		}
		return out;
	}

}


int main() {

	size_t id = 10;
	vec::vector<bool> v1("100000000000001");

	std::cout << v1 << '\n';

	v1.erase(id);

	std::cout << v1 << '\n';

	v1.insert(id, true);

	std::cout << v1 << '\n';

	return 0;

}
