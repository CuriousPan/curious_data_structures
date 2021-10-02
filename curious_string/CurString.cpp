#ifndef CUR_STRING_CPP
#define CUR_STRING_CPP

#include "CurString.h"

unsigned int _str_size_(const char*);
void _copy_(const char*, char*, unsigned int);
void _free_(const char*);
bool _compare_str_(const char*, const char*, unsigned int size);

CurString::CurString(const char* string, unsigned int additional_buffer_size)
{
	m_length = _str_size_(string);
	m_capacity = m_length + additional_buffer_size;
	m_data = new char[sizeof(char) * m_capacity];
	for(int i = 0; i < m_capacity; ++i)
	{
		m_data[i] = 'e';
	}
	_copy_(string, m_data, m_length);
	m_data[m_length] = '\0'; //that seems to be a wacky solution, but that's what I've got
}

CurString::CurString(const CurString& string)
: CurString(string.m_data, string.m_capacity - string.m_length)
{
}

CurString::CurString(const std::string& string, unsigned int additional_buffer_size)
: CurString(string.c_str(), additional_buffer_size)
{
}

CurString::~CurString()
{
	_free_(m_data);
}

CurString& CurString::operator=(const CurString& string) //TODO(think about assignment operator without allocating new buffer in some cases)
{
	if (this == &string)
	{
		 return *this;
	}
	m_length = string.m_length;
	m_capacity = string.m_capacity;
	_free_(m_data);
	m_data = new char[sizeof(char) * m_capacity];
	_copy_(string.m_data, m_data, m_length);
	return *this;
}

void CurString::append(const CurString& string)
{
	if (m_length + string.m_length < m_capacity)
	{
		_copy_(string.m_data, m_data + m_length, string.m_length);
		m_length += string.m_length;
		m_data[m_length] = '\0';
	}
	else
	{
		char* newData = new char[sizeof(char) * (m_length + string.m_length + 17)];
		_copy_(m_data, newData, m_length);
		_copy_(string.m_data, newData + m_length, string.m_length);
		_free_(m_data);
		m_data = newData;
		m_capacity = m_length + string.m_length + 17;
		m_length += string.m_length;
	}
}

std::string CurString::toString() const
{
	return std::string(m_data, m_length);
}

const char* CurString::toCString() const
{
	return m_data;
}

void CurString::trim()
{
	if (m_length == 0)
	{
		return;
	}
	int i = m_length - 1;
	for (i; m_data[i] == ' ' && i != -1; --i)
	{
		--m_length;
	}
	m_data[i+1] = '\0';
	if (m_data[0] != ' ')
	{
		return;
	}
	i = 0;
	for (i; m_data[i] == ' ' && i != m_length; ++i)
	{
		--m_length;
	}
	_copy_(m_data + i, m_data, m_length);
	m_data[m_length] = '\0';
}

bool CurString::startsWith(const CurString& string) const
{
	if (string.m_length == 0 || string.m_length > m_length)
	{
		return false;
	}
	for (int i = 0; i < string.m_length; ++i)
	{
		if (string.m_data[i] != m_data[i])
		{
			return false;
		}
	}
	return true;
}

bool CurString::endsWith(const CurString& string) const
{

	if (string.m_length == 0 || string.m_length > m_length)
	{
		return false;
	}
	for (int i = string.m_length - 1, k = m_length - 1; i > -1; --i, --k)
	{
		if (string.m_data[i] != m_data[k])
		{
			return false;
		}
	}
	return true;
}

CurString CurString::subString(unsigned int start) const
{
	return subString(start, m_length);
}

CurString CurString::subString(unsigned int start, unsigned int end) const
{
	if (start < 0 || start >= m_length || end <= 0 || end > m_length || start >= end)
	{
		throw std::out_of_range("Provided indeces are out of bounds");
	}
	CurString string("", (end - start) + 17);
	_copy_(m_data + start, string.m_data, end - start);
	string.m_length = end - start;
	string.m_data[string.m_length] = '\0';
	return string;
}

bool CurString::contains(const CurString& string) const
{
	if (string.m_length == 0 || string.m_length > m_length)
	{
		return false;
	}
	for (int i = 0;string.m_length + i <= m_length; ++i)
	{	
		std::cout << m_data+i << " " << string.m_data << std::endl;
		if (_compare_str_(m_data + i, string.m_data, string.m_length))
		{
			return true;
		}
	}
	return false;
}

void CurString::remove(unsigned int start, unsigned int end)
{
	if (start < 0 || start >= m_length || end <= 0 || end > m_length || start >= end)
	{
		throw std::out_of_range("Provided indeces are out of bounds");
	}
	_copy_(m_data + end, m_data + start, m_length - end);
	m_length -= (end - start);
	m_data[m_length] = '\0';
}

void CurString::remove(unsigned int start)
{
	return remove(start, start + 1);
}

int CurString::firstIndex(const char* character) const
{
	for (unsigned int i = 0; i != m_length; ++i)
	{
		if (m_data[i] == *character)
		{
			return i;
		}
	}
	return -1;
}

int CurString::lastIndex(const char* character) const
{

	for (int i = m_length - 1; i != -1; --i)
	{
		if (m_data[i] == *character)
		{
			return i;
		}
	}
	return -1;
}

void CurString::reverse()
{
	char tmp;
	for (int i = 0, g = m_length - 1; i < g; ++i, --g)
	{
		tmp = m_data[i];
		m_data[i] = m_data[g];
		m_data[g] = tmp;
	}
}

unsigned int CurString::length() const
{
	return m_length;
}

unsigned int CurString::capacity() const
{
	return m_capacity;
}

const char& CurString::at(unsigned int index) const
{
	if (0 <= index && index < m_length)
	{
		return m_data[index];
	}
	else
	{
		throw std::out_of_range("Provided index is out of bounds");
	}
}

char& CurString::at(unsigned int index)
{
	if (0 <= index && index < m_length)
	{
		return m_data[index];
	}
	else
	{
		throw std::out_of_range("Provided index is out of bounds");
	}
}

const char& CurString::operator[](int index) const 
{
	return at(index);
}

char& CurString::operator[](int index) 
{
	return at(index);
}

std::ostream& operator<<(std::ostream& stream, const CurString& string)
{
	for (int i = 0; i < string.m_length; ++i)
	{
		stream << string.m_data[i];
	}
	return stream;
}

CurString operator+(const CurString& lstring, const CurString& rstring)
{
	CurString string;
	string.append(lstring);
	string.append(rstring);	
	return string;
}

bool CurString::operator==(const CurString& string) const
{
	if (m_length == string.m_length)
	{
		return (_compare_str_(m_data, string.m_data, m_length));
	}
	return false;
}

bool CurString::operator!=(const CurString& string) const
{
	if (m_length == string.m_length)
	{
		return (!_compare_str_(m_data, string.m_data, m_length));
	}
	return true;
}

CurString CurString::operator+=(const CurString& string)
{
	append(string);
	return *this;
}

CurString::StringIterator::StringIterator(char* ptr)
{
	m_ptr = ptr;
}

CurString::StringIterator CurString::StringIterator::operator++(int)
{
	CurString::StringIterator iterator(m_ptr);
	++m_ptr;
	return iterator;
}

CurString::StringIterator& CurString::StringIterator::operator++()
{
	++m_ptr;
	return *this;
}

CurString::StringIterator CurString::StringIterator::operator--(int)
{
	CurString::StringIterator iterator(m_ptr);
	--m_ptr;
	return iterator;
}

CurString::StringIterator& CurString::StringIterator::operator--()
{
	--m_ptr;
	return *this;
}

char& CurString::StringIterator::operator[](int index)
{
	return *(m_ptr + index);
}

char* CurString::StringIterator::operator->()
{
	return m_ptr;
}

char& CurString::StringIterator::operator*()
{
	return *m_ptr;
}

bool CurString::StringIterator::operator==(const CurString::StringIterator& iterator) const
{
	return m_ptr == iterator.m_ptr;
}

bool CurString::StringIterator::operator!=(const CurString::StringIterator& iterator) const
{
	return m_ptr != iterator.m_ptr;
}

CurString::StringIterator CurString::begin()
{
	return StringIterator(m_data);
}

CurString::StringIterator CurString::end()
{
	return StringIterator(m_data + m_length);
}

unsigned int _str_size_(const char* string)
{
	int size = 0;
	while (*string != '\0')
	{
		++size;
		++string;
	}
	return size;
}

void _copy_(const char* source, char* dest, unsigned int size)
{
	unsigned int current = 0;
	while(current != size)
	{
		*dest = *source;
		++source;
		++dest;
		++current;
	}
}

void _free_(const char* string)
{
	delete [] string;
}

bool _compare_str_(const char* lstring, const char* rstring, unsigned int size)
{
	unsigned int current = 0;
	while (current++ != size)
	{
		if (*(lstring++) != *(rstring++))
		{
			return false;
		}
	}
	return true;
}


#endif

//summer-717
