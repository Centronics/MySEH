#pragma once
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

template<typename T1, typename T2> auto Plus(T1&& t1, T2&& t2) -> decltype(forward<T1>(t1) + forward<T2>(t2))
{
	return forward<T1>(t1) + forward<T2>(t2);
}

class X
{
	friend X operator+(const X& x1, const X& x2)
	{
		return X(x1._mData + x2._mData);
	}

public:
	explicit X(const int data) : _mData(data) {}
	[[nodiscard]] int Dump() const { return _mData; }
private:
	int _mData;
};

inline void DeclTypeDemo()
{
	// Integer
	int i = 4;
	cout <<
		"Plus(i, 9) = " <<
		Plus(i, 9) << endl;

	// Floating point
	float dx = 4.0;
	float dy = 9.5;
	cout <<
		setprecision(3) <<
		"Plus(dx, dy) = " <<
		Plus(dx, dy) << endl;

	// String
	string hello = "Hello, ";
	string world = "world!";
	cout << Plus(hello, world) << endl;

	// Custom type
	X x1(20);
	X x2(22);
	const X x3 = Plus(x1, x2);
	cout <<
		"x3.Dump() = " <<
		x3.Dump() << endl;
}