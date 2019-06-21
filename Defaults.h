#pragma once
#include <algorithm>

using namespace std;

class A
{
public:
	int Op;
};

inline void DefaultsDemo()
{
	A a{ 0 }, b{ 10 };
	a = move(b);
	a.Op = 11;
	b = a;
	a.Op = 12;
	A c(move(a));
	c.Op = 13;
	A d(c);
}

/*
���������� C++ �� ��������� ���������� ��������� �������:
	1. ����������� ��-��������� (default constructor)
	2. ����������� ����������� (copy constructor)
	3. �������� ������������ (assignment operator)
	4. ���������� (destructor)
	������ (������� � �++11) ���:
	5. ����������� ����������� (move constructor)
	6. �������� ������������ ������������ (move assignment operator)

	����� ������������� �������� ������ ������� ������������ ���������� ������������ �������� ��������������� �������.
*/