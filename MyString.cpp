#include "MyString.h"

void MyString::copyFrom(const MyString& other)
{
	str = new char[strlen(other.str) + 1];
	size = other.size;
	strcpy_s(str, size + 1, other.str);
}
void MyString::free()
{
	delete[] str;
}
void MyString::moveFrom(MyString&& other)
{
	str = other.str;
	size = other.size;
	other.str = nullptr;
	other.size = 0;
}

MyString::MyString()
{
	str = nullptr;
	size = 0;
}
MyString::MyString(const char* _str)
	:str(nullptr), size(0)
{
	if (_str == nullptr)
	{
		return;
	}

	size_t len = strlen(_str);
	str = new char[len + 1];
	size = len;
	strcpy_s(str, size + 1, _str);
}
MyString::MyString(const MyString& other)
{
	copyFrom(other);
}
MyString::MyString(MyString&& other) noexcept
{
	moveFrom(std::move(other));
}
MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
MyString::~MyString()
{
	free();
}

const char MyString::operator[](size_t index) const
{
	return str[index];
}

char& MyString::operator[](size_t index)
{
	return str[index];
}

void MyString::toUpper()
{
	for (size_t i = 0; i < size; i++)
	{
		if (str[i] < 'A' || str[i]>'Z')
			str[i] -= 'a' - 'A';
	}
}

void MyString::concat(const MyString& other)
{
	size = size + other.size;
	char* tem = new char[size + 1];
	strcpy_s(tem, strlen(str) + 1, str);
	strcat_s(tem, size + 1, other.str);			// s +1 bez +1 ?
	free();
	str = tem;
}
size_t MyString::getSize() const
{
	return size;
}

const char* MyString::c_str() const
{
	return str;
}

MyString& MyString::operator+=(const MyString& other)
{
	concat(other);
	return *this;
}

std::ostream& operator<<(std::ostream& os, const MyString& string)
{
	os << string.str;
	return os;
}

std::istream& operator>>(std::istream& is, MyString& string)
{
	char buff[1024];
	is >> buff;
	size_t len = strlen(buff);

	delete[] string.str;
	string.str = new char[len + 1];
	strcpy_s(string.str, len + 1, buff);
	string.size = len;

	return is;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString str1 = lhs;
	str1 += rhs;
	return str1;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}
bool operator>(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}