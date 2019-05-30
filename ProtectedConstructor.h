#pragma once

class A
{
	A() = default;
	friend class B;
};

class B
{
public:
	B() = default;

	A GetA()
	{
		return A();
	}
};

inline void ProtectedConstructorDemo()
{
	size_t sza = sizeof(A), szb = sizeof(B);
	B b;
	A a = b.GetA();
	// A v; // Не получится так написать, т.к. конструктор класса "A" закрыт.
}