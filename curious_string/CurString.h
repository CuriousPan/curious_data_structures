#ifndef CUR_STRING_H
#define CUR_STRING_H

#include <iostream>
#include <string>



class CurString
{

	public:
	class StringIterator
	{
	public:
		StringIterator(char* ptr);
		StringIterator operator++(int);
		StringIterator& operator++();
		StringIterator operator--(int);
		StringIterator& operator--();
		bool operator==(const StringIterator& iterator) const;
		bool operator!=(const StringIterator& iterator) const;
		char& operator[](int index);
		char* operator->();
		char& operator*();

	private:
		char* m_ptr;
	};

public:
	CurString(const char* string = "", unsigned int additional_buffer_size = 17);
	CurString(const CurString& string);
	CurString(const std::string& string, unsigned int additional_buffer_size = 17);
	~CurString();

	unsigned int length() const;
	unsigned int capacity() const;
	const char& at(unsigned int index) const;
	char& at(unsigned int index);
	void append(const CurString& string);
	std::string toString() const;
	const char* toCString() const;
	void trim();
	bool startsWith(const CurString& string) const;
	bool endsWith(const CurString& string) const;
	CurString subString(unsigned int start) const;
	CurString subString(unsigned int start, unsigned int end) const;
	void remove(unsigned int start);
	void remove(unsigned int start, unsigned int end);
	bool contains(const CurString& string) const;
	int firstIndex(const char* character) const;
	int lastIndex(const char* character) const;
	void reverse();

	friend std::ostream& operator<<(std::ostream& stream, const CurString& string);
	friend CurString operator+(const CurString& lstring, const CurString& rstring);
	bool operator==(const CurString& string) const;
	bool operator!=(const CurString& string) const;
	CurString& operator=(const CurString& string);
	const char& operator[](int index) const;
	char& operator[](int index);
	CurString operator+=(const CurString& string);

	StringIterator begin();
	StringIterator end();

private:
	char* m_data;
	unsigned int m_length;
	unsigned int m_capacity;

};

#endif
