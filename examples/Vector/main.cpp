#include <iostream>

class Dummy
{
public:
	Dummy(){
		std::cout << "Hello world!\n";
	}
};

template <typename Type>
class Vector
{
private:
	Type* m_data;
	size_t m_size;
	size_t m_capacity;
public:
	Vector(size_t capacity = 0): m_size(0), m_capacity(capacity){
		if (m_capacity != 0)
		{
			m_data = reinterpret_cast<Type*>(::operator new(new_capacity * sizeof(Type)));
			for (size_t idx = 0; idx < m_size; ++idx)
				new(tmp + idx) Type; // placement new
		}
	}

	void clear()
	{
		if (m_capacity != 0)
		{
			for (size_t idx = 0; idx < m_size; ++idx)
                m_data[idx].~Type();
			::operator delete[] (m_data);
			m_size = m_capacity = 0;
		}
	}

	void reserve(size_t capacity){
		resize(capacity);
		m_size = capacity;
	}

	void resize(size_t new_capacity){
		if (new_capacity < m_capacity)
			m_size = new_capacity;
		if (new_capacity > m_capacity){
			
			// Type* tmp = new Type[new_capacity];
			Type* tmp = reinterpret_cast<Type*>(::operator new(new_capacity * sizeof(Type)));
			for (size_t idx = 0; idx < m_size; ++idx)
				//tmp[idx] = m_data[idx]; // operator=(tmp[idx], m_data[idx]); -> fail, because tmp[idx] is raw memory
				new(tmp + idx) Type(std::move(m_data[idx])); // placement new

			clear();
			m_capacity = new_capacity;
			m_data = tmp;
		}
	}

	void push_back(Type const& val){
		if (m_size == m_capacity){
			resize(m_capacity * 1.5);
		}
		m_data[m_size++] = val;
	}

	Type& operator[](int idx){
		return m_data[idx];
	}

	~Vector(){
		clear();
	}

	size_t size() const {
		return m_size;
	}
};

template <>
class Vector<bool>
{
private:
	unsigned char* buf;
	size_t m_bit_size;
	size_t m_byte_size;
public:
	Vector(size_t bit_size = 0) : m_bit_size(bit_size), m_byte_size(bit_size / 8 + 1) {
		if (m_byte_size != 0)
			buf = new char[m_byte_size];
	}

	size_t size() const {
		return m_bit_size;
	}

	void push_back(bool val){
		if (m_bit_size < m_byte_size * 8) {
			int bit_idx = m_bit_size % 8;
			if (val)
				buf[m_bit_size / 8] |= 1 << bit_idx;
			else
				buf[m_bit_size / 8] &= ~(1 << bit_idx);
		}
	}

	class BoolVecElement;

	// b_vec[i] = 0;
	BoolVecElement operator[] (int idx){
		char byte = buf[idx/8];
		return (byte >> idx) & 1;
	}

	class BoolVecElement{
		//unsigned char* byte;
		//size_t bit_idx;
		//operator=: bool -> byte[bit_idx]
		//bool: return byte[bit_idx]
	}
};

int main()
{
	size_t const SZ = 3;
	Vector<Dummy> vec;

	vec.reserve(SZ);

	// // for (int val = 5; val > 0; --val)
	// // 	vec.push_back(val);

	// for (int idx = 0; idx < vec.size(); ++idx)
	// 	vec[idx] = idx*idx;

	// for (size_t idx = 0; idx < vec.size(); ++idx)
	// 	std::cout << vec[idx] << '\t';
	// std::cout << "\n";

	Vector<bool> b_vec(3);
	b_vec.push_back(1);
	std::cout << b_vec[0] << "\n";
	b_vec[0] = 0;

	return 0;
}
