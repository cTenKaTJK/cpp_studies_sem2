#include <iostream>
#include <fstream>

class DataReader
{
protected:
	std::ifstream m_in;
	std::string m_filename;
	uint8_t* m_data;
	uint8_t m_n;

public:
	DataReader(const std::string& filename) : m_filename(filename), m_n(0), m_data(nullptr) {}

	virtual ~DataReader() {}

	virtual bool Open() = 0;
	void Close() { m_in.close(); }

	virtual void Read() = 0;
	virtual void Write() = 0;

	void GetData(uint8_t* buf, uint8_t& n) {
		n = m_n;
		for (int i = 0; i < m_n; i++)
			buf[i] = m_data[i];
	}

	void GetBigData(float* buf, unsigned int& n) {
		n = m_n;
		memcpy(buf, m_data, 4 * n);
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
		m_data = new uint8_t[m_n];
		for (int i = 0; i < m_n; i++)
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
		m_in.open(m_filename, std::ios::binary | std::ios::in);
		if (!m_in.is_open())
			return false;
		return true;
	}

	void Read() override {
		m_in.read((char*)&m_n, 1);
		m_data = new uint8_t[m_n];
		m_in.read((char*)m_data, m_n);
	}

	void Write() override {}
};


enum class Type { TXT, BIN };

std::unique_ptr<DataReader> Factory(const std::string& filename)
{
	std::string extension = filename.substr(filename.find_last_of('.') + 1);

	if (extension == "txt") return std::make_unique<TxtReader>(filename);

	else if (extension == "bin")  return std::make_unique<BinReader>(filename);

	return nullptr;
}

void fill_file(const std::string& filename) {
	const unsigned int n = 3;
	float buf[n] = { 3.14f, 10.05f, 18.901f };

	std::fstream file(filename, std::ios::out | std::ios::binary);
	file.write((char*)&n, 1);
	file.write((char*)a, 4 * n);
	file.close();
}

int main() {

	unsigned int n;
	float buf[20];

	fill_file("./files/input.bin");

	auto Reader = Factory("./files/input.bin");

	if (Reader == nullptr)
		return -1;

	Reader->Open();
	Reader->Read();
	Reader->GetBigData(buf, n);

	std::cout << (int)n << std::endl;
	for (unsigned i = 0; i < n; i++)
		std::cout << std::bitset<32>(*(uint32_t*)(&buf[i])).to_string() << ' ' << buf[i] << std::endl;

	return 0;
}
