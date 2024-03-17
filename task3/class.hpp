#pragma once


namespace st {

	class String {

	private:

		char* str_;
		int len_;

	public:

		String();

		String(const char* chars);

		~String();

		String(const String& other);

		String& operator=(const String& other);

		String& operator+=(const String& other);

		String operator+(const String& other);

		bool operator==(const String& other);

		bool operator<(const String& other);

		bool operator>(const String& other);

		char& operator[](const size_t index);

		const char& operator[](const size_t index) const;

		friend std::ostream& operator<<(std::ostream& out, const String& other);
		friend std::istream& operator>>(std::istream& in, String& other);

		void swap(String& other);

		int find(char sym);

		int length();

		char* c_str();

		char at(int index);

		void at(int index, char value);

	};

	std::ostream& operator<<(std::ostream& out, const String& other);

	std::istream& operator>>(std::istream& in, String& other);

}
