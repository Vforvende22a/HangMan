#pragma once
#include <iostream>>
class MyString
{
private:
	char* str;
	size_t size;

	void copyFrom(const MyString& other);
	void free();
	void moveFrom(MyString&& other);

public:
	MyString();
	MyString(const char* _str);
	MyString(const MyString& other);
	MyString(MyString&& other)noexcept;
	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other)noexcept;
	~MyString();

	const char operator[](size_t index)const;
	char& operator[](size_t index);

	void toUpper();
	void concat(const MyString& other);
	size_t getSize() const;
	const char* c_str() const;


	MyString& operator+=(const MyString& other);

	friend std::ostream& operator<<(std::ostream& os, const MyString& string);
	friend std::istream& operator>>(std::istream& is, MyString& string);
};

MyString operator+(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);