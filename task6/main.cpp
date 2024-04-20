#include<iostream>
#include<bitset>
#include<cstring>


namespace vec {

	template<typename T>
	class vector {};

	template<>
	class vector<bool> {

	private:
		char* data_;
		size_t len_;
		int cell_;

	public:
		vector() {
			len_ = 0;
			cell_ = -1;
			data_ = new char[1];
		}

		~vector() { delete[] data_; }

		vector(const vector& other) {
			len_ = other.len_;
			data_ = other.data_;
			cell_ = other.cell_;
		}

		void pushback(bool value) {
			if (len_ % 8 == 0) {
				extend();
				cell_++;
				data_[cell_] = 0 | value;
			}
			else {
				data_[cell_] = data_[cell_] << 1;
				data_[cell_] = data_[cell_] | value;
			}
			len_++;
		}

		size_t size() {
			return len_;
		}
		
		void extend() {
			if (cell_ = -1) {
				data_ = new char[1];
			}
			else {
				char* tmp = new char[cell_ + 1];
				for (size_t i = 0; i < cell_; i++) {
					char c = data_[i];
					tmp[i] = c;
				}
				data_ = tmp;
				delete[] tmp;
			}
		}
		bool operator[] (size_t index) {}
		
		/*
		void erase(size_t index) {
			vector<bool> slice1, slice2, tmp = *this;
			for (size_t i = 0; i < len_; i++) {
				if (i < index)
					slice1.pushback(tmp[i]);
				else if (i > index) {
					slice1.pushback(false);
					slice2.pushback(tmp[i]);
				}
			}
			data_ = slice1.data_ | slice2.data_;
			len_--;
		}

		void insert(size_t index, bool value) {}
		*/

		friend std::ostream& operator<<(std::ostream& out, vector<bool>& item);
	};


	std::ostream& operator<<(std::ostream& out, vector<bool>& item) {
		for (size_t i = 0; i < item.cell_; i++) {
			std::bitset<8> bs = item.data_[i];
			out << bs.to_string();
		}
		std::bitset<8> bs = item.data_[item.cell_];
		out << bs.to_string().substr(8 - item.len_ % 8, item.len_ % 8);
		return out;
	}

}


int main() {
	vec::vector<bool> v;

	v.pushback(true);
	std::cout << v << '\n';
	v.pushback(false);
	std::cout << v << '\n';
	v.pushback(true);
	std::cout << v << '\n';

	return 0;
}
