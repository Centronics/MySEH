#pragma once
#include <initializer_list>

using namespace std;

// ¬ enum по умолчанию int.

class A
{
public:
	int Tt[2]{};

	A(initializer_list<int>) { Tt[0] = 12, Tt[1] = 13; }
	//A()=default; // ≈сли написать { }, выбираетс€ конструтор по умолчанию.
};

class B
{
	int _tt[2]{};
	inline static int _ip = 0;

public:
	B(initializer_list<int>) { _tt[0] = _ip++, _tt[1] = _ip++; }
	//B()=default; // ≈сли написать { } при инициализации, выбираетс€ конструтор по умолчанию.
};

inline void EqualDemo()
{
	A a1{};
	A a2{};
	a2.Tt[0] = 14;
	a2.Tt[1] = 15;
	a1 = a2; // ¬нутри типа массивы приравниваютс€.

	B b1{};
	const B b2{};
	b1 = b2; // ¬нутри типа массивы приравниваютс€.
}