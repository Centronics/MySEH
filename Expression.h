#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class SomeClass
{
	//int _i; Даже если убрать эту переменную, то ничего не изменится в поведении класса при перемещении.
public:
	SomeClass() = default; // То же самое, что {}.
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

inline SomeClass MeReturn() // Конструктор копирования НЕ будет вызван.
{
	return SomeClass{}; // Копирование и перемещение будет пропущено. То же самое, что ().
}

/*inline SomeClass MeReturn() // Конструктор копирования будет вызван.
{
	SomeClass some{};
	return some;
}*/

/*inline SomeClass MeReturn() // Конструктор копирования будет вызван.
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
	//Class() = default; // Такая запись означает то же самое, что полное отсутствие конструкторов.
	Class() {	} // В этом случае ни в одном инициализаторе t НЕ будет инициализирована, т.к. она не инициализирована в конструкторе.
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
	a = 12; // a и b не являются ссылками, а являются копиями.
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

	Class c{}; // t не публичная, поэтому она не отобразится. t БУДЕТ инициализирована. Если есть конструктор по умолчанию, то он будет вызван, но при этом t не будет инициализирована, если она в нём не прописана.
	Class d; // t НЕ БУДЕТ инициализирована. Если есть конструктор по умолчанию, то он будет вызван, но при этом t не будет инициализирована. Если его нет, то t НЕ будет инициализирована.
	Class j = Class(); // t БУДЕТ инициализирована. При этом нельзя написать: Class j(). В этом случае результат неизвестен. Если есть конструктор по умолчанию, то он будет вызван, но при этом t не будет инициализирована.

	int i1 = 1;
	// ReSharper disable once CppAssignedValueIsNeverUsed
	i1 = i1++ + i1++; // Вначале происходит сложение переменной самой с собой.
	//Этот код уходит "вникуда", т.е. он сохраняет результат как значение переменной "i1" во временную переменную, затем берёт из "i1" значение и сохраняет его в неё же, увеличив на один, затем делает это же второй раз, получая значение два, после этого это значение затирается из временной переменной.
	//Значение временной переменной и есть итоговый результат.
	//Если значение переменной i1 изначально было ноль, то она и будет ноль в итоге.
	//Если изначально была единица, то будет два.

	int value = 0;
	(cout << "first\n", value++) && (cout << "second\n", value++);
	GetFunc(value++, value++);

	// ReSharper disable once CppDeclaratorNeverUsed
	auto some = MeReturn();
	MeAccept(some);// Если написать some, то конструктор копирования будет вызван, если SomeClass{} - нет.

	int mas[3], i = 0;
	mas[i++] = i++; // Сначала берёт значение i (в конце), затем увеличивает его, запоминая старое. Далее запоминается старое значение в операторе [] и происходит инкремент. Таким образом, получается, что элементу с индексом 1 будет присвоено значение 0. i будет равна 2.

	value = i = 0;
	int p = (i = 1) << (value = 2); // = 4.

	//Первый результат гарантировано будет 4, тогда как второй может быть как 2, так и 4. Этот пример хорошо показывает разницу между явным и неявным вызовом перегруженного оператора в C++17.
	i = 0;
	int result = SomeClass1{ i = 1 } << (i = 2);
	cout << "First result: " << result << "\n";
	result = operator<<(SomeClass1{ i = 1 }, i = 2); // Сначала выполняется i = 2, затем i = 1. В конструктор подастся единица. result будет равен двум.
	cout << "Second result: " << result << "\n";

	/*for (int k = 0;
		(k = 9, k = 8) >= 0; // Сначала выполняется k = 9, потом k = 8.
		k++);*/ // Если раскомментить, то зависнет.

	const B<double> b;
	A(), 1, b; // Сначала A::int, затем B, т.е. выражение (A(), 1) берёт аргумент b.
	A(), b, 1; // Работает в обратном порядке.

	i = 1'000; // 1000.
}