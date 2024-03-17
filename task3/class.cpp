#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include"class.hpp"


namespace st {

	String::String() : String("") {}

	String::String(const char* chars) {
		int c = 0;
		while (chars[c] != '\0')
			c++;
		str_ = new char[c];
		strcpy(str_, chars);
		len_ = c;
	}

	String::~String() {}

	String::String(const String& other) {
		len_ = other.len_;
		str_ = other.str_;
	}

	String& String::operator=(const String& other) {
		len_ = other.len_;
		str_ = other.str_;
		return *this;
	}

	String& String::operator+=(const String& other) {
		int i = 0;
		while (other.str_[i] != '\0') {
			str_[len_ + i] = other.str_[i];
			i++;
		}
		len_ += other.len_;
		str_[len_] = '\0';
		return *this;
	}

	String String::operator+(const String& other) {
		String blank(str_);
		blank += other;
		return blank;
	}

	bool String::operator==(const String& other) {
		if (len_ != other.len_)
			return false;
		else {
			for (int i = 0; i < len_; i++) {
				if (str_[i] != other.str_[i])
					return false;
			}
			return true;
		}
	}

	bool String::operator<(const String& other) {
		if (len_ < other.len_)
			return true;
		else if (len_ > other.len_)
			return false;
		else {
			for (int i = 0; i < len_; i++) {
				if (str_[i] < other.str_[i])
					return true;
				else if (str_[i] > other.str_[i])
					return false;
			}
			return false;
		}
	}

	bool String::operator>(const String& other) {
		if (len_ > other.len_)
			return true;
		else if (len_ < other.len_)
			return false;
		else {
			for (int i = 0; i < len_; i++) {
				if (str_[i] > other.str_[i])
					return true;
				else if (str_[i] < other.str_[i])
					return false;
			}
			return false;
		}
	}

	const char& String::operator[](const size_t index) const {
		if (index <= len_)
			return str_[index];
	}

	char& String::operator[](const size_t index) {
		if (index <= len_)
			return str_[index];
	}

	void String::swap(String& other) {
		std::swap(str_, other.str_);
		std::swap(len_, other.len_);
	}

	int String::find(char sym) {
		int i = 0;
		while (str_[i] != '\0') {
			if (str_[i] == sym)
				return i;
			i++;
		}
		return -1;
	}

	int String::length() {
		return len_;
	}

	char* String::c_str() {
		return str_;
	}

	char String::at(int index) {
		if (index > len_)
			return NULL;
		return str_[index];
	}

	void String::at(int index, char value) {
		if (index <= len_) {
			str_[index] = value;
		}
	}

	std::ostream& operator<<(std::ostream& out, const String& other) {
		for (int i = 0; i < other.len_; i++) {
			out << other.str_[i];
		}
		return out;
	}

	std::istream& operator>>(std::istream& in, String& other) {
		char* chars = new char[100];
		int i = 0;
		in >> chars;
		while (chars[i] != '\0') {
			i++;
		}
		other.len_ = i;
		chars[i + 1] = '\0';
		other.str_ = chars;
		return in;
	}

}
