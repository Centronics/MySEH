#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;

inline void ExprTest();
inline void ExprCycle();

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
	ExprTest();
	ExprCycle();

	[[maybe_unused]] S s2 = { 10, 'c' };

	const TetStr tst{};
	auto[a, bc] = tst;
	a = 12; // a � b �� �������� ��������, � �������� �������.
	bc = 19.9;
	// auto&[a1, bc1] = tst; // ��� ������ ������.

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

inline void ExprTest()
{
	int a[] = { 1, 2, 3, 4, 5, 6 };
	const int a2 = 3[a - 1] - a[3] + (a - 1)[5]; // (3 - 4) + 5 = 4;
	const int a3 = a[2] - a[3] + a[4]; // �� �� �����.
	cout << "a2 = " << a2 << "; a3 = " << a3 << endl;

	char str[6] = "emacs"; // str[5] �������� ������.
	cout << str << endl;

	// ���������������� �� �������? ����� ��� ������� �������?

	// int a <::> = <%1, 2, 3, 4, 5, 6%>; // �� ��������������.
}

inline void ExprCycle()
{
	[[maybe_unused]] const auto t = 25u - 50; // ��� unsigned int.
	[[maybe_unused]] const auto y = 25 - 50u; // ��� unsigned int.
	[[maybe_unused]] const auto w = -25 - 50u; // ��� unsigned int.
	[[maybe_unused]] const auto z = 25u - -50; // ��� unsigned int.
	[[maybe_unused]] const auto p = 3.14 - 3.14f; // ��� double.
	[[maybe_unused]] const auto d = 3.14f - 3.14; // ��� double.
	[[maybe_unused]] const auto h = 0xFFFFFFFF; // 0xFFFFFFFF - unsigned int; 0xFF - signed int.
	[[maybe_unused]] const auto j = 4294967295; // unsigned long.
	[[maybe_unused]] const auto s = 429496729;  // int.
	[[maybe_unused]] const auto a = 0xFFFFFFFFFFFFFFFF; // unsigned long long.
	[[maybe_unused]] const auto q = 0xFFFFFFFF - 1; // unsigned int.
	[[maybe_unused]] const auto v = 0xFFFFFFFF + 1; // unsigned int.
	// [[maybe_unused]] const auto b = 0x10000000000000000; // ������� ������� ��������.

	const char ch = 1;
	[[maybe_unused]] auto fg = ch * 2; // int. ����, ���� �������� (char).
	[[maybe_unused]] auto fq = 2 * ch; // int. ����, ���� �������� (char).

	/*unsigned char half_limit = 150; // ���������.
	for (unsigned char i = 0; i < 2 * half_limit; ++i)
	{
		//���-�� ����������;
	}*/
}