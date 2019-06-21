#pragma once
#include <algorithm>

using namespace std;

class A
{
public:
	int Op;
};

inline void DefaultsDemo()
{
	A a{ 0 }, b{ 10 };
	a = move(b);
	a.Op = 11;
	b = a;
	a.Op = 12;
	A c(move(a));
	c.Op = 13;
	A d(c);
}

/*
Компилятор C++ по умолчанию генерирует следующие функции:
	1. конструктор по-умолчанию (default constructor)
	2. конструктор копирования (copy constructor)
	3. оператор присваивания (assignment operator)
	4. деструктор (destructor)
	Теперь (начиная с С++11) ещё:
	5. конструктор перемещения (move constructor)
	6. оператор присваивания перемещением (move assignment operator)

	Чтобы предотвратить создание данных функций компилятором необходимо предоставить описание соответствующих функций.
*/