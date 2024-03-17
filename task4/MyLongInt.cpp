#define _CRT_SECURE_NO_WARNINGS
#include<cmath>
#include<iostream>
#include<cstring>
#include "MyLongInt.hpp"


namespace lt {

	MyLongInt::MyLongInt(std::string str) {
		if (str[0] == '-') {
			is_negative_ = true;
			str = str.substr(1, str.length() - 1);
		}
		reverse(str.begin(), str.end());
		len_ = str.length() / SEG_;
		if (str.length() % SEG_)
			len_++;
		for (int i = 0; i < len_; i++) {
			int segment = 0, end = SEG_, ln = str.length();
			if (ln < SEG_) end = ln;
			for (int j = 0; j < end; j++)
				segment += to_int(str[j]) * pow(10, j);
			num_[i] = segment;
			if (ln >= SEG_) str = str.substr(SEG_, ln - SEG_);
		}
	}

	MyLongInt::MyLongInt(const char* c) {
		std::string str = c;
		this->MyLongInt::MyLongInt(str);
	}

	MyLongInt::MyLongInt(const MyLongInt& other) {
		len_ = other.len_;
		is_negative_ = other.is_negative_;
		for (int i = 0; i < len_; i++)
			num_[i] = other.num_[i];
	}

	MyLongInt& MyLongInt::operator=(const MyLongInt& other) {
		len_ = other.len_;
		is_negative_ = other.is_negative_;
		for (int i = 0; i < len_; i++)
			num_[i] = other.num_[i];
		return *this;
	}

	MyLongInt& MyLongInt::operator+=(MyLongInt& other) {
		bool swapped = false;
		MyLongInt blank;
		if (len_ < other.len_ || ((len_ == other.len_) && (num_[len_ - 1] < other.num_[len_ - 1]))) {
			blank = other;
			swap(other);
			swapped = true;
		}
		int ln = len_, nxt = 0;
		for (int i = 0; i < ln; i++) {
			if (is_negative_ != other.is_negative_)
				num_[i] -= other.num_[i];
			else
				num_[i] += other.num_[i];
			num_[i] += nxt;
			if (num_[i] >= pow(10, SEG_)) {
				num_[i] -= pow(10, SEG_);
				nxt = 1;
			}
			else if (num_[i] < 0 && i != ln - 1) {
				num_[i] += pow(10, SEG_);
				nxt = -1;
			}
			else
				nxt = 0;
		}
		if (nxt == 1) {
			len_++;
			num_[len_ - 1] = 1;
		}
		if (num_[len_ - 1] == 0 && len_ > 1)
			len_--;
		if (num_[len_ - 1] < 0) {
			num_[len_ - 1] = abs(num_[len_ - 1]);
			is_negative_ = true;
		}
		if (swapped) other = blank;
		return *this;
	}

	MyLongInt MyLongInt::operator+(MyLongInt& other) {
		MyLongInt blank = *this;
		blank += other;
		return blank;
	}

	MyLongInt MyLongInt::operator*=(MyLongInt& other) {
		bool swapped = false;
		MyLongInt blank;
		if (len_ < other.len_) {
			MyLongInt blank;
			blank = other;
			swap(other);
			swapped = true;
		}
		int n[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		for (int i = 0; i < len_; i++) {
			for (int j = 0; j < other.len_; j++) {
				n[i] += num_[i] * other.num_[j] * pow(pow(10, SEG_), j);
				if (n[i] >= pow(10, SEG_)) {
					n[i + 1] = n[i] / int(pow(10, SEG_));
					n[i] %= int(pow(10, SEG_));
				}
			}
		}
		{
			int i = 0;
			while (n[i])
				i++;
			len_ = i;
		}
		for (int i = 0; i < len_; i++)
			num_[i] = n[i];
		if (is_negative_ != other.is_negative_) is_negative_ = true;
		else is_negative_ = false;
		if (swapped) other = blank;
		return *this;
	}

	MyLongInt MyLongInt::operator*(MyLongInt& other) {
		MyLongInt blank = *this;
		blank *= other;
		return blank;
	}

	bool MyLongInt::operator==(const MyLongInt& other) {
		if (is_negative_ != other.is_negative_ || len_ != other.len_)
			return false;
		for (int i = 0; i < len_; i++) {
			if (num_[i] != other.num_[i])
				return false;
		}
		return true;
	}

	bool MyLongInt::operator!=(const MyLongInt& other) {
		if (is_negative_ != other.is_negative_ || len_ != other.len_)
			return true;
		for (int i = 0; i < len_; i++) {
			if (num_[i] != other.num_[i])
				return true;
		}
		return false;
	}

	bool MyLongInt::operator<(const MyLongInt& other) {
		if (is_negative_ != other.is_negative_) {
			if (is_negative_) return true;
			else return false;
		}
		if (len_ < other.len_) return true;
		else if (len_ > other.len_) return false;
		else {
			for (int i = len_ - 1; i >= 0; i--) {
				if (num_[i] < other.num_[i]) return true;
				else if (num_[i] > other.num_[i]) return false;
			}
			return false;
		}
	}

	bool MyLongInt::operator>(const MyLongInt& other) {
		if (is_negative_ != other.is_negative_) {
			if (is_negative_) return false;
			else return true;
		}
		if (len_ > other.len_) return true;
		else if (len_ < other.len_) return false;
		else {
			for (int i = len_ - 1; i >= 0; i--) {
				if (num_[i] > other.num_[i]) return true;
				else if (num_[i] < other.num_[i]) return false;
			}
			return false;
		}
	}

	void MyLongInt::swap(MyLongInt& other) {
		std::swap(num_, other.num_);
		std::swap(len_, other.len_);
		std::swap(is_negative_, other.is_negative_);
	}

	std::istream& operator>>(std::istream& in, MyLongInt& item) {
		std::string str;
		in >> str;
		item = MyLongInt(str);
		return in;
	}

	std::ostream& operator<<(std::ostream& out, const MyLongInt& item) {
		if (item.is_negative_)
			out << '-';
		for (int i = item.len_ - 1; i > -1; i--) {
			int dg = dg_c(item.num_[i]);
			if (!item.num_[i]) {
				for (int x = 0; x < item.SEG_; x++)
					out << '0';
				out << '`';
			}
			else if ((dg < item.SEG_) && (i != (item.len_ - 1))) {
				for (int x = 0; x < (item.SEG_ - dg); x++)
					out << '0';
				out << item.num_[i] << '`';
			}
			else {
				out << item.num_[i] << '`';
			}
		}
		return out;
	}

	int to_int(char c) {
		if (c == '0') return 0;
		if (c == '1') return 1;
		if (c == '2') return 2;
		if (c == '3') return 3;
		if (c == '4') return 4;
		if (c == '5') return 5;
		if (c == '6') return 6;
		if (c == '7') return 7;
		if (c == '8') return 8;
		if (c == '9') return 9;
	}

	int dg_c(int x) {
		int c = 1;
		while (x >= 10) {
			c++;
			x /= 10;
		}
		return c;
	}

}

