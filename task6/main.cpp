#include<iostream>
#include<bitset>
#include<cstring>


namespace vec {

	template<typename T>
	class vector {};

	template<>
	class vector<bool> {

	private:
		char data_;
		size_t len_;

	public:
		vector() {
			len_ = 0;
			data_ = 0;
		}

		~vector() { /* delete[] data_; */ }

		vector(const vector& other) {
			len_ = other.len_;
			data_ = other.data_;
		}

		void pushback(bool value) {
			char tmp = data_;
			tmp = tmp << 1;
			tmp = tmp | value;
			data_ = tmp;
			len_++;
		}

		bool operator[] (size_t index) {
			vector<bool> mask;
			mask.pushback(true);
			for (size_t i = 0; i < (len_ - index - 1); i++)
				mask.pushback(false);
			return mask.data_ & data_;
		}

		size_t size() {
			return len_;
		}

		void erase(size_t index) {
			vector<bool> slice1, slice2, tmp = *this;
			for(size_t i = 0; i < len_; i++) {
				if (i < index)
					slice1.pushback(tmp[i]);
				else if (i > index)
					slice2.pushback(tmp[i]);
			}
			for (size_t i = 0; i < (len_ - index - 1); i++)
				slice1.pushback(false);
			data_ = slice1.data_ | slice2.data_;
			len_--;
		}

		void insert(size_t index, bool value) {}

		friend std::ostream& operator<<(std::ostream& out, vector<bool>& item);
	};

	std::ostream& operator<<(std::ostream& out, vector<bool>& item) {
		std::bitset<8> bs = item.data_;
		out << bs.to_string().substr(8 - item.len_, item.len_);
		return out;
	}

}


int main() {
	vec::vector<bool> v;

	v.pushback(true);
	v.pushback(true);
	v.pushback(false);
	v.pushback(false);
	v.pushback(true);

	std::cout << v << '\n';

	std::cout << v[3] << '\n';
	v.erase(3);

	std::cout << '\n' << v << '\n';

	return 0;
}