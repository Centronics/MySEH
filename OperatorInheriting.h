#pragma once

class A
{
public:
	int operator[](size_t) const // �������� ����������� � ����� ����������.
	{
		return 10;
	}
};

class B : public A
{

};

inline void OperatorInherDemo()
{
	const B b;
	// ReSharper disable once CppDeclaratorNeverUsed
	auto i = b[0];
}