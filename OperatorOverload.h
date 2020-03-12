#pragma once
#include <iostream>

//struct A;

//A operator+(const A&);

struct A
{
	//A operator+(const A&){return A();} // Неоднозначность, если раскомментить.
	//friend A operator+(const A&);
	~A()
	{
		std::cout << "1";
		//throw 1;
	}
};

/*A& A::operator+(A&)
{
}*/

A operator+(A&, const A&) { return A(); }

void OperatorOverloadExample()
{
	try
	{
		A a;
		a = a + A();
		throw 2;
	}
	catch (...)
	{
		return;
	}
}