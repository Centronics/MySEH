#pragma once
#include <iostream>
#include <functional>
#include <algorithm>

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
		byte bt = static_cast<byte>(50); // C++17. Требуется строгое преобразование.
		double D::* ptr = &D::DB; // Член не должен быть статическим.
		int G::* ptr1 = &G::PG; // Член не должен быть статическим.
		double D::* ptr2 = &G::DB; // Член не должен быть статическим.
		void(*pv)() = &D::fun; // Только static.
		auto fg = this->*ptr2; // this обязателен.
		this->*ptr2 = 2.3; // this обязателен.
	}
};

class SD
{
public:
	int IO;
};

class SD1
{
public:
	int IO;
	double HJ;
};

class SD3
{
public:
	int OP;
};

class SD4 : public SD3
{
public:
	double RT;
};

class cls
{
public:
	int t, y;
};

class cls11
{
public:
	cls11() : t(), y() {} // Подходит default.

	int t, y;
};

class cls2
{
public:
	cls2(int) {}
	int o = 2;
};

class clls3
{
public:
	clls3() = delete;
	int o = 2;
};

class ClsConstr
{
public:
	ClsConstr() = default;
	double dbl;

public:
	int io = 0;
};

class ClsConstr1 : public ClsConstr
{
public:
	ClsConstr1() = default;
	double _dbl;

public:
	int _io = 0;
};

class ClsMas
{
	int u;
public:
	ClsMas() = default; // Если {}, то u не инициализируется.
	ClsMas(int) {}
};

template<auto Constant> void ConstantPrinter() // C++17
{
	if constexpr (is_convertible_v<decltype(Constant), size_t>) // Компилируется статически.
		cout << "Constant provided: " << Constant << "\n";
	else
		cout << "Null pointer provided.\n";
}

template<auto Constant> void ConstantPrinter1()
{
	if (is_convertible_v<decltype(Constant), int>) // Компилируется как обычно.
		cout << "Constant provided: " << Constant << "\n";
	else
		cout << "Null pointer provided.\n";
}

inline void TstTemplateDemo()
{
	ConstantPrinter<1>();
	ConstantPrinter1<2>();

	ClsConstr constr = { }; // Инициализировать члены можно только в случае, если все они public и даже в том случае, если одному из них задано значение по умолчанию. Инициализация возможна в случае, если конструктор = default, но не определён. Вне зависимости от атрибута доступа конструктора.
	ClsConstr con1{};
	ClsConstr1 ctr; // Не инициализированы.
	ClsConstr1 ctr1{}; // Инициализированы.
	ClsConstr1 ctr2 = {}; // Инициализированы.
	ClsConstr1 ctr3(); // Переменная не будет видна.

	SD sd = { 47 };
	SD1 sd1 = { 34,43.6 };
	SD4 sd4 = { {3}, 5.5 };
	SD4 sdg{}; // Будут инициализированы.
	cls cl{}; // Будут инициализированы.
	cls dl; // НЕ будут инициализированы. () нельзя писать. Размер класса становится равным единице.
	cls dl1 = cls(); // Будут инициализированы.
	//cls1 cls1(); // () нельзя писать. Размер класса становится равным единице.
	cls11* pcls1 = new cls11; // Можно и (), можно и без. Инициализации не будет! Если конструктор = default. Если есть недефолтный конструктор, то всё будет работать как обычно.
	cls11* pcls2 = new cls11(); // Можно и (), можно и без. Инициализация будет! Если конструктор = default. Если есть недефолтный конструктор, то всё будет работать как обычно.
	cls2 cls22(8); // Работает ТОЛЬКО тогда, когда есть конструктор НЕ по умолчанию.
	cls2 cls3 = cls2(9); // Работает.
	clls3 cl3(); // ОК. Если так написать, то переменная видна не будет вне зависимости от того, удалён конструктор или нет.
	// clls3 cl5; // Ошибка: конструктор по умолчанию удалён.
	// clls3 cl4 = clls3(); // Нельзя так писать, если конструктор = delete.

	ClsMas* clsma1 = new ClsMas[25];
	ClsMas* clsmas = new ClsMas[25](); // Если консруктор по умолчанию = default, то инициализация будет.
	int* a1 = new int[10]; // НЕТ инициализации.
	int* a2 = new int[10](); // ВСЕ элементы будут инициализированы.

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

	vector<string> v = { "a1", "ab1", "abc1" }; // Выведется 2, 3, 4.
	vector<size_t> l;
	transform(v.begin(), v.end(), back_inserter(l),
		mem_fn(&string::size));
	for (size_t n : l)
		cout << n << ' ';
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