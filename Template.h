#pragma once
#include <iostream>

using namespace std;

template<typename T> class TstTemplate
{
public:
	static T Func()
	{
		return T();
	}
};

template<> class TstTemplate <double>
{
public:
	static int Func()
	{
		return 5;
	}
};

template<typename T = char> T Foo()
{
	return T();
}

template<> inline double Foo()
{
	return 9.9;
}

// partial_specialization_of_class_templates.cpp
template <class T> struct PTS {
	enum {
		IS_POINTER = 0,
		IS_POINTER_TO_DATA_MEMBER = 0
	};
};

template <class T> struct PTS<T*> {
	enum {
		IS_POINTER = 1,
		IS_POINTER_TO_DATA_MEMBER = 0
	};
};

template <class T, class U> struct PTS<T U::*> {
	enum {
		IS_POINTER = 0,
		IS_POINTER_TO_DATA_MEMBER = 1
	};
};

struct S {};

class D
{
public:
	double DB;
	static void fun() {}
};

class G : public D
{
public:
	int PG;
	void fin() {}

	void VoidG()
	{
		double D::* ptr = &D::DB; // Член не должен быть статическим.
		int G::* ptr1 = &G::PG; // Член не должен быть статическим.
		double D::* ptr2 = &G::DB; // Член не должен быть статическим.
		void(*pv)() = &D::fun; // Только static.
		auto fg = this->*ptr2; // this обязателен.
		this->*ptr2 = 2.3; // this обязателен.
	}
};

inline void TstTemplateDemo()
{
	printf_s("PTS<int S::*>::IsPointer == %d PTS <int S::*>::IsPointerToDataMember == %d\n", PTS<int S::*>::IS_POINTER, PTS<int S::*>::IS_POINTER_TO_DATA_MEMBER);

	auto a = TstTemplate<double>::Func();
	auto t = TstTemplate<int>::Func();

	auto i = Foo<int>();
	auto p = Foo<double>();
	auto c = Foo();

	cout << "a = " << a << " (" << typeid(a).name() << ")" << endl;
	cout << "t = " << t << " (" << typeid(t).name() << ")" << endl << endl;

	cout << "i = " << i << " (" << typeid(i).name() << ")" << endl;
	cout << "p = " << p << " (" << typeid(p).name() << ")" << endl;
	cout << "c = " << c << " (" << typeid(c).name() << ")" << endl;
}

class A {
public:
protected:
	int i;
};


class B : public A {
	friend void f(A*, B*);
	void g(A*);
};

void f(A* pa, B* pb) {
	//  pa->i = 1;
	pb->i = 2;

	//  int A::* point_i = &A::i;
	int A::* point_i2 = &B::i;
}

void B::g(A* pa) {
	//  pa->i = 1;
	i = 2;

	//  int A::* point_i = &A::i;
	int A::* point_i2 = &B::i;
}