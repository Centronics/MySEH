#pragma once

class A
{
public:
	int operator[](size_t) // Оператор наследуется и будет вызываться.
	{
		return 10;
	}
};

class B : public A
{

};

inline void OperatorInherDemo()
{
	B b;
	auto i = b[0];
}