#pragma once
#include <any>
#include <iostream>
#include <string>
#include <utility>
#include <functional>

using namespace std;

class AD
{
public:

	AD(int) {}

	AD& operator= (float f)
	{
		return *this;
	}

	operator float() const // ≈сли добавить explicit, то будет требоватьс€ €вное преобразование.
	{
		return 78.8f;
	}

	/*operator int() const // ≈сли раскомментировать, получитс€ двусмысленный cout.
	{
		return 66;
	}*/

	bool operator== (const AD& ad) const noexcept
	{
		return true;
	}
};

inline void AnyTest()
{
	// simple example

	auto a = any(12);

	cout << any_cast<int>(a) << '\n';

	try {
		cout << any_cast<string>(a) << '\n';
	}
	catch (const bad_any_cast& e) {
		cout << e.what() << '\n';
	}

	// pointer example

	if (int* i = any_cast<int>(&a)) {
		cout << "a is int: " << *i << '\n';
	}
	else if (string* s = any_cast<string>(&a)) {
		cout << "a is string: " << *s << '\n';
	}
	else {
		cout << "a is another type or unset\n";
	}

	// advanced example

	a = string("hello");

	auto& ra = any_cast<string&>(a); //< reference
	ra[1] = 'o';

	cout << "a: " << any_cast<const string&>(a) << '\n'; //< const reference

	const auto b = any_cast<string&&>(move(a)); //< rvalue reference

	// Note: 'b' is a move-constructed string,
	// 'a' is left in valid but unspecified state

	cout << "a: " << *any_cast<string>(&a) //< pointer
		<< "b: " << b << '\n';
}

inline void AnyDemo()
{
	cout << boolalpha;

	AnyTest();

	// any type
	any a = 1;
	cout << a.type().name() << ": " << any_cast<int>(a) << '\n';
	a = 3.14;
	cout << a.type().name() << ": " << any_cast<double>(a) << '\n';
	a = true;
	cout << a.type().name() << ": " << any_cast<bool>(a) << '\n';

	// bad cast
	try
	{
		a = 1;
		cout << any_cast<float>(a) << '\n';
	}
	catch (const bad_any_cast& e)
	{
		cout << e.what() << '\n';
	}

	AD ad(9);
	a = ad;
	cout << "Type = \"" << a.type().name() << "\"; AD = " << any_cast<AD>(a) << '\n';
	[[maybe_unused]] auto tt = &ad; // AD*

	const float flt = ad;
	ad = flt;

	// has value
	a = 1;
	if (a.has_value())
	{
		cout << a.type().name() << '\n';
	}

	// reset
	a.reset();
	if (!a.has_value())
	{
		cout << "no value\n";
	}

	// pointer to contained data
	a = 1;
	cout << "typeid(int) = \"" << typeid(int).name() << "\" typeid(int*) = \"" << typeid(int*).name() << "\" typeid(int) == typeid(int*) = \"" << (typeid(int*) == typeid(int)) << "\"" << endl;
	int* i = any_cast<int>(&a);
	cout << *i << "\n";
	a = 2.23; // double
	[[maybe_unused]] float* pf = any_cast<float>(&a); // nullptr

	int top = 10;
	const auto fhh = [&top]
	{
		top++;
	};

	const std::function<void()> f_func = fhh;
	f_func();
}