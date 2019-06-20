#pragma once
#include <iostream>
#include <cstdarg>

using namespace std;

inline void VarFun(int count, ...)
{
	va_list args;
	va_start(args, count);
	for (int i = 0; i < count; ++i)
		cout << va_arg(args, int) << endl;
	va_end(args);
}

inline void MyFun(int count, ...)
{
	va_list args;
	va_start(args, count);
	cout << va_arg(args, double) << endl;
	cout << va_arg(args, char) << endl;
	cout << va_arg(args, unsigned int) << endl;
	va_end(args);
}

inline void VarArgsTest()
{
	VarFun(3, 7, 8, 9);
	MyFun(3, 3.4, 'c', 23u);
}