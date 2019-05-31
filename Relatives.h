#pragma once
#include <algorithm>
#include <iostream>

struct A
{
	int CA = 9;
	double CB = 4.5;

	A() = default; // ����� ��� ����, ����� ������� { }.

	A(const A& a)
	{

	}
};

class C
{
public:
	int U = 3;
	A a;
};

class D
{
public:
	int P;

	//D(double, float) {} // ���� ���� �����������, �� ����� ����� �� � ��, ��� ���� �� ���������. ���� ��� ���, �� ����� ����� ����� ������.
};

inline void RelativesDemo()
{
	D d = D{ 3 }; // ���� � �� ��.
	D d1 = { 3 }; // ���� � �� ��.
	D d2{ 3 };    // ���� � �� ��.

	A a21;
	A a = { A() }; // ����� ������� �������� ������������ ��� �������� ������.
	A a11;
	C c = { 7 };
	C v = std::move(c); // �������� ����������� �����������.

	int array[] = { 1, 3, 5, 7, 9 }; // �������� ����������!!!
	auto[a1, a2, a3, a4, a5] = array;
	std::cout << "Third element before: "
		<< a3 << "(" << array[2] << ")\n";
	a3 = 4;
	std::cout << "Third element after: "
		<< a3 << "(" << array[2] << ")\n";
}