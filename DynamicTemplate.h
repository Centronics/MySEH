#pragma once
#include <iostream>

using namespace std;

//#define OLDSTYLE

#if defined OLDSTYLE

template<typename... Ts> class Printer;

template<typename T, typename... Ts> class Printer<T, Ts...> : public T, public Printer<Ts...>
{
public:
	using T::operator();
	using Printer<Ts...>::operator();
};

template<> class Printer<>
{
public:
	void operator()() const {}
};

#else

template<typename... Ts> class Printer : public Ts...
{
public:
	using Ts::operator()...;
	using Ts::F...;
};

#endif

class IntPrinter
{
public:
	void operator()(const int i) const
	{
		cout << "Int passed: " << i << "\n";
	}

	static void F()
	{
		cout << "f called" << endl;
	}
};

class FloatPrinter
{
public:
	void operator()(const float f) const
	{
		std::cout << "Float passed: " << f << "\n";
	}

	[[nodiscard]] static int F(const float t)
	{
		cout << "f called" << endl;
		return static_cast<int>(t);
	}
};

inline void DynamicTemplateDemo()
{
	const Printer<IntPrinter, FloatPrinter> printer;
	printer(55);
	printer(55.1f);
	Printer<IntPrinter, FloatPrinter>::F();
	int t = Printer<IntPrinter, FloatPrinter>::F(45.5f);
}