#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class SomeClass
{
	//int _i; ���� ���� ������ ��� ����������, �� ������ �� ��������� � ��������� ������ ��� �����������.
public:
	SomeClass() = default; // �� �� �����, ��� {}.
	SomeClass(const SomeClass&)
	{
		cout << "Copy ctor called.\n";
	}

	SomeClass(SomeClass&&) noexcept
	{
		try
		{
			cout << "Move ctor called.\n";
		}
		catch (...)
		{

		}
	}
};

inline SomeClass MeReturn() // ����������� ����������� �� ����� ������.
{
	return SomeClass{}; // ����������� � ����������� ����� ���������. �� �� �����, ��� ().
}

/*inline SomeClass MeReturn() // ����������� ����������� ����� ������.
{
	SomeClass some{};
	return some;
}*/

/*inline SomeClass MeReturn() // ����������� ����������� ����� ������.
{
	SomeClass some{};
	if (false)
		return SomeClass{};
	return some;
}*/

inline void _stdcall GetFunc(int a, int b)
{

}

inline void MeAccept([[maybe_unused]] SomeClass s)
{

}

class SomeClass1
{
	friend int operator<<(const SomeClass1& obj, int&);

public:
	explicit SomeClass1(const int var) : _mVar{ var }
	{

	}

private:
	int _mVar;
};

inline int operator<<(const SomeClass1& obj, int& shift)
{
	return obj._mVar << shift;
}

template < class T > class B {};

class A
{
public:
	A& operator, (int index)
	{
		cout << "A::" << typeid(index).name() << " = " << index << endl;
		return *this;
	}

	template<typename T> A& operator, (const B<T>& b)
	{
		cout << typeid(b).name() << endl;
		return *this;
	}
};

class Class
{
	int t, *r;
public:
	//Class() = default; // ����� ������ �������� �� �� �����, ��� ������ ���������� �������������.
	Class() {	} // � ���� ������ �� � ����� �������������� t �� ����� ����������������, �.�. ��� �� ���������������� � ������������.
};

struct TetStr
{
	int a = 13;
	double b = 20.2;
};

inline decltype(auto) Func()
{
	return 0.0L;
}

inline auto Funt() -> int
{
	return 0;
}

template<typename T, typename U> struct S
{
	T m_first;
	U m_second;
	S(T first, U second) : m_first(first), m_second(second) {}
};

inline void TestExpression()
{
	[[maybe_unused]] S s2 = { 10, 'c' };

	const TetStr tst{};
	auto[a, bc] = tst;
	a = 12; // a � b �� �������� ��������, � �������� �������.
	bc = 19.9;

	vector<int> vct = { 1, 2, 3 };

	decltype(auto) r = vct.emplace_back(10);
	r = 43;

	for (const auto &i : vct)
	{
		std::cout << i << ' ';
	}

	map<int, char> myMap;

	for (const auto &[key, value] : myMap)
	{
		std::cout << "key: " << key << ' ';
		std::cout << "value: " << value << '\n';
	}

	Class c{}; // t �� ���������, ������� ��� �� �����������. t ����� ����������������. ���� ���� ����������� �� ���������, �� �� ����� ������, �� ��� ���� t �� ����� ����������������, ���� ��� � �� �� ���������.
	Class d; // t �� ����� ����������������. ���� ���� ����������� �� ���������, �� �� ����� ������, �� ��� ���� t �� ����� ����������������. ���� ��� ���, �� t �� ����� ����������������.
	Class j = Class(); // t ����� ����������������. ��� ���� ������ ��������: Class j(). � ���� ������ ��������� ����������. ���� ���� ����������� �� ���������, �� �� ����� ������, �� ��� ���� t �� ����� ����������������.

	int i1 = 1;
	// ReSharper disable once CppAssignedValueIsNeverUsed
	i1 = i1++ + i1++; // ������� ���������� �������� ���������� ����� � �����.
	//���� ��� ������ "�������", �.�. �� ��������� ��������� ��� �������� ���������� "i1" �� ��������� ����������, ����� ���� �� "i1" �������� � ��������� ��� � �� ��, �������� �� ����, ����� ������ ��� �� ������ ���, ������� �������� ���, ����� ����� ��� �������� ���������� �� ��������� ����������.
	//�������� ��������� ���������� � ���� �������� ���������.
	//���� �������� ���������� i1 ���������� ���� ����, �� ��� � ����� ���� � �����.
	//���� ���������� ���� �������, �� ����� ���.

	int value = 0;
	(cout << "first\n", value++) && (cout << "second\n", value++);
	GetFunc(value++, value++);

	// ReSharper disable once CppDeclaratorNeverUsed
	auto some = MeReturn();
	MeAccept(some);// ���� �������� some, �� ����������� ����������� ����� ������, ���� SomeClass{} - ���.

	int mas[3], i = 0;
	mas[i++] = i++; // ������� ���� �������� i (� �����), ����� ����������� ���, ��������� ������. ����� ������������ ������ �������� � ��������� [] � ���������� ���������. ����� �������, ����������, ��� �������� � �������� 1 ����� ��������� �������� 0. i ����� ����� 2.

	value = i = 0;
	int p = (i = 1) << (value = 2); // = 4.

	//������ ��������� ������������� ����� 4, ����� ��� ������ ����� ���� ��� 2, ��� � 4. ���� ������ ������ ���������� ������� ����� ����� � ������� ������� �������������� ��������� � C++17.
	i = 0;
	int result = SomeClass1{ i = 1 } << (i = 2);
	cout << "First result: " << result << "\n";
	result = operator<<(SomeClass1{ i = 1 }, i = 2); // ������� ����������� i = 2, ����� i = 1. � ����������� �������� �������. result ����� ����� ����.
	cout << "Second result: " << result << "\n";

	/*for (int k = 0;
		(k = 9, k = 8) >= 0; // ������� ����������� k = 9, ����� k = 8.
		k++);*/ // ���� �������������, �� ��������.

	const B<double> b;
	A(), 1, b; // ������� A::int, ����� B, �.�. ��������� (A(), 1) ���� �������� b.
	A(), b, 1; // �������� � �������� �������.

	i = 1'000; // 1000.
}