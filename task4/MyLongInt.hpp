#pragma once


namespace lt{

	class MyLongInt {

	private:

		int len_;
		
		int num_[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	//3 * 10 = 30 digits value

		const int SEG_ = 3; //max item value = 999 (10 ^ 3 - 1)
		
		bool is_negative_ = false;	//1 - if num < 0; else - 1

	public:

		MyLongInt() : MyLongInt("0") {};

		MyLongInt(std::string num);

		MyLongInt(const char* c);

		~MyLongInt() {};

		MyLongInt(const MyLongInt& other);

		MyLongInt& operator=(const MyLongInt& other);

		MyLongInt& operator+=(MyLongInt& other);

		MyLongInt operator+(MyLongInt& other);

		MyLongInt operator*=(MyLongInt& other);

		MyLongInt operator*(MyLongInt& other);

		void swap(MyLongInt& other);

		friend std::istream& operator>>(std::istream& in, MyLongInt& item);

		friend std::ostream& operator<<(std::ostream& out, const MyLongInt& item);

	};

	std::istream& operator>>(std::istream& in, MyLongInt& item);

	std::ostream& operator<<(std::ostream& out, const MyLongInt& item);

	int dg_c(int x);
	
	int to_int(char c);

}