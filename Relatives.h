#pragma once
#include <algorithm>
#include <iostream>

struct A
{
	int CA = 9;
	double CB = 4.5;

	A() = default; // Нужен для того, чтобы работал { }.

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

	//D(double, float) {} // Если есть конструктор, то будет виден он и те, что есть по умолчанию. Если его нет, то будут видны члены класса.
};

inline void RelativesDemo()
{
	D d = D{ 3 }; // Одно и то же.
	D d1 = { 3 }; // Одно и то же.
	D d2{ 3 };    // Одно и то же.

	A a21;
	A a = { A() }; // Можно вписать аргумент конструктора или оставить пустым.
	A a11;
	C c = { 7 };
	C v = std::move(c); // Вызывает конструктор копирования.

	int array[] = { 1, 3, 5, 7, 9 }; // Привязки КОПИРУЮТСЯ!!!
	auto[a1, a2, a3, a4, a5] = array;
	std::cout << "Third element before: "
		<< a3 << "(" << array[2] << ")\n";
	a3 = 4;
	std::cout << "Third element after: "
		<< a3 << "(" << array[2] << ")\n";
}