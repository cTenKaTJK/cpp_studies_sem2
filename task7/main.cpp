#include <iostream>
#include <fstream>
#include <memory>
#include <bitset>

// N < 256 и a_i < 256, для всех i=1..N
// .txt - массив данных в формате N и a_i, где i=1..N (ASCII)
// .bin - массив данных в формате N и a_i, где i=1..N (bin)
// float 1 бит предназначен для хранения знака, 8 бит для экспоненты и 23 для мантиссы, что в сумме дает 32 бита

class DataReader
{
protected:
	std::ifstream m_in;
	std::string m_filename;
	uint32_t* m_data;
	unsigned int m_n;

public:
	DataReader(const std::string& filename) : m_filename(filename), m_n(0), m_data(nullptr) {}

	virtual ~DataReader() {}

	virtual bool Open() = 0;
	virtual void Read() = 0;
	virtual void Write() = 0;

	void Close() {
		m_in.close();
	}

	virtual void GetData(uint32_t* buf, unsigned& n) {
		n = m_n;
		for (unsigned short i = 0; i < m_n; i++)
			buf[i] = m_data[i];
	}
};

class TxtReader : public DataReader
{
public:
	TxtReader(const std::string& filename) : DataReader(filename) {}

	virtual ~TxtReader() {
		if (m_data != nullptr)
			delete[] m_data;
	}

	bool Open() override {
		m_in.open(m_filename);
		if (!m_in.is_open())
			return false;
		return true;
	}

	void Read() override {
		int tmp;
		m_in >> tmp;
		m_n = tmp;
		m_data = new uint32_t[m_n];
		for (unsigned short i = 0; i < m_n; i++)
		{
			int tmp;
			m_in >> tmp;
			m_data[i] = tmp;
		}
	}

	void Write() override {}

};

class BinReader : public DataReader
{
public:
	BinReader(const std::string& filename) : DataReader(filename) {}

	virtual ~BinReader() {
		if (m_data != nullptr)
			delete[] m_data;
	}

	bool Open() override {
		m_in.open(m_filename, std::ios::binary);
		if (!m_in.is_open())
			return false;
		return true;
	}

	void Read() override {
		m_in.read((char*)&m_n, 1);
		m_data = new uint32_t[m_n];
		for (unsigned short i = 0; i < m_n; i++) {
			uint8_t byte;
			m_in.read((char*)&byte, 1);
			m_data[i] = byte;
		}
		m_in.read((char*)m_data, m_n);
	}

	void Write() override {}
};

class BinFloatReader : public DataReader
{
protected:
	uint32_t* m_bigData;

public:
	BinFloatReader(const std::string& filename) : DataReader(filename) { m_bigData = nullptr; }

	virtual ~BinFloatReader() {
		if (m_data != nullptr)
			delete[] m_data;
	}

	bool Open() override {
		m_in.open(m_filename, std::ios::binary);
		return m_in.is_open();
	}

	void GetBigData(uint32_t* buf, unsigned& n) {
		n = m_n;
		for (unsigned short i = 0; i < m_n; i++)
			buf[i] = m_bigData[i];
	}

	void Read() override {
		/*
		uint8_t old_n = m_n;
		m_in.read((char*)&m_n, 1);
		m_n *= 4;

		if (m_n > old_n) {
			delete[] m_data;
			m_data = new uint8_t[m_n];
		}
		else if (!m_data && m_n != 0) {
			m_data = new uint8_t[m_n];
		}

		m_in.read((char*)m_data, m_n);
		*/
		/*
		std::ifstream in("input2.bin", std::ios::binary);
		uint8_t n;
		in.read((char*)&n, 1);

		uint8_t* buf = new uint8_t[n];
		in.read((char*)buf, n);

		std::cout << (int)n << std::endl;

		for (int i = 0; i < n; i++)
			std::cout << (int)buf[i] << std::endl;

		delete[] buf;
		*/
		m_in.read((char*)&m_n, 1);
		unsigned bytes_len = m_n * 4;
		std::cout << (int)m_n << '\n';

		uint8_t byte;
		m_in.read((char*)&byte, 1);
		uint32_t num = byte;

		for (unsigned short i = 1; i < bytes_len; i++) {
			if (i % 4 == 0) {
				m_bigData[(i / 4) - 1] = num;
				//uint8_t byte;
				m_in.read((char*)&byte, 1);
				num = byte;
				byte = 0;
				std::cout << "->|||copyed to buf|||<-\n";
			}
			else {
				num = num << 8;
				m_in.read((char*)&byte, 1);
				num = num | byte;
				byte = 0;
			}
		}
		m_bigData[m_n - 1] = num;
		std::cout << "->|||copyed to buf|||<-\n";

	}

	void Write() override {}
};


enum class Type {UINT8_T, FLOAT, TXT};

std::unique_ptr<DataReader> Factory(const std::string& filename, Type type)
{
	std::string extension = filename.substr(filename.find_last_of('.') + 1);

	if (extension == "txt") return std::make_unique<TxtReader> (filename);

	else if (extension == "bin" && type == Type::UINT8_T)  return std::make_unique<BinReader>(filename);

	else if (extension == "bin" && type == Type::FLOAT) return std::make_unique<BinFloatReader>(filename);

	return nullptr;
}

void fill_file(const std::string& filename) {
	std::fstream file(filename, std::ios::out | std::ios::binary);
	const unsigned int n = 3;

	uint32_t buff[n] = { 8, 16, 32 };

	file.write((char*)&n, 4);
	for (unsigned short i = 0; i < n; i++) file.write((char*)buff[i], 4);
	file.close();

}

int main() {
/*
	std::ifstream file;
	file.open("./files/input.bin", std::ios::binary);
	uint8_t num;
	file.read((char*)&num, 1);
	std::cout << (int)num << ' ' << std::bitset<8>(num).to_string() << '\n';
*/
	
	unsigned int n;
	uint32_t buf[20];

	fill_file("./files/input.bin");

	auto Reader = Factory("./files/input.bin", Type::UINT8_T);

	if (Reader == nullptr)
		return -1;

	Reader->Open();
	Reader->Read();
	Reader->GetData(buf, n);

	std::cout << (int)n << std::endl;
	for (unsigned i = 0; i < n; i++)
		std::cout << (int)buf[i] << std::endl;
	
	/*
	{
		const uint8_t n = 12;
		uint8_t data[n]{ 129, 129, 129, 129,
			128, 0, 0, 0,
			0, 128, 0, 0};
		uint32_t f = data[0];
		uint32_t buf[3];

		std::cout << 0 << ' ' << std::bitset<32>(f).to_string() << ' ' << std::bitset<8>(data[0]).to_string() << '\n';

		for (short i = 1; i < n; i++) {
			if (i % 4 == 0) {
				buf[(i / 4) - 1] = f;
				f = data[i];
				std::cout << "->|||copyed to buf|||<-\n";
			}
			else {
				f = f << 8;
				f = f | data[i];
			}

			std::cout << i << ' ' << std::bitset<32>(f).to_string() << ' ' << std::bitset<8>(data[i]).to_string() << '\n';
		}
		buf[(n / 4) - 1] = f;
		std::cout << "->|||copyed to buf|||<-\n";

		std::cout << '\n';

		for (short i = 0; i < n / 4; i++) std::cout << (float)buf[i] << '\t' << std::bitset<32>(buf[i]).to_string() << '\n';
	}
	*/
	/*
	
		uint32_t f = m_data[0];

		std::cout << 0 << ' ' << std::bitset<32>(f).to_string() << ' ' << std::bitset<8>(m_data[0]).to_string() << '\n';

		for (short i = 1; i < n; i++) {
			if (i % 4 == 0) {
				buf[(i / 4) - 1] = f;
				f = m_data[i];
				std::cout << "->|||copyed to buf|||<-\n";
			}
			else {
				f = f << 8;
				f = f | m_data[i];
			}

			std::cout << i << ' ' << std::bitset<32>(f).to_string() << ' ' << std::bitset<8>(m_data[i]).to_string() << '\n';
		}
		buf[(n / 4) - 1] = f;
		std::cout << "->|||copyed to buf|||<-\n";
	*/

	return 0;
}