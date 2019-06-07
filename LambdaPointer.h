#pragma once
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <typeinfo>
#include <functional>

using namespace std;
using Func = function<void()>;

inline void FillVectorExample(vector<int>& v) // ���� ����� ���� �� ������, �� ����� � ���������� vector<int>() ����� �� � �������������� � ���, ��� ��� ������������� ���������� Microsoft.
{
	// A local static variable.
	static int nextValue = 1;

	// The lambda expression that appears in the following call to
	// the generate function modifies and uses the local static
	// variable nextValue.
	generate(v.begin(), v.end(), [] { return nextValue++; }); // �������� ������ �� 1 �� 10.
	//WARNING: this is not thread-safe and is shown for illustration only
}

class LambdaTest
{
	double _dbl = 1.1;

public:
	Func MyFuncZ, MyFunc;

	Func Ff = [] // ��� ���� ����� ���������������� ������.
	{
		// ReSharper disable once CppDeclaratorNeverUsed
		int a = 67;
	};

	void LambdaPointerDemo()
	{
		int a = 10, b = 20;
		const auto f = [=]() -> void
		{
			// ReSharper disable once CppDeclaratorNeverUsed
			int t = a; // "a" �������� ������.
		};

		auto d = [a, &b]() mutable noexcept -> void // mutable ������������ ������ ��������� ����������, ���������� �� ��������. �������� ���������� ������ ������ ������, ��� ���� �������� ���� ���������� ��� const ������. ��������, ���������� �� �������, ����� �������� ������.
		{
			a++; // ����� �������� �������� ����������� ���������� ��-�� mutable.
			b = 12;
		};

		/*auto j = []() // �� �������.
		{
			int y = a; // ��������� �� "a" ������ ���� ��� ������. [] - �������� ���������� ����������� ����������.
		};*/

		void(*h)() = []() // ������������� ��������� �� �������. ������������ ���������� � ������ �� ���������. ������������� ���� ��������� �� ������� �� ��������� � ������ �������� ����������� ����������, �.�. ��� ����� �������� � ��������.
		{
			// ReSharper disable once CppDeclaratorNeverUsed
			int e = 0; // ������������ "a" ������ �� � ����� ������, �.�. ��� �� ���������; // _asm �� �������������� ��� �����.
		};

		// ���� �������� "*this", �� ����� ��������� ����� � ��� �������� ����� �����������. ��������� ������� ����� �� ����� �������� ������. �������� "a" ������������ ��� ������ �� ������� ���� �������, �������� "b" ������ ����������.
		MyFuncZ = [*this, &a, b]() // ������������� ��������� �� �������. ������������ ���������� � ������ �� ���������. ������������� ���� ��������� �� ������� �� ��������� � ������ �������� ����������� ����������, �.�. ��� ����� �������� � ��������.
		{
			// ReSharper disable once CppDeclaratorNeverUsed
			auto e = _dbl; // ������������ "a" ������ �� � ����� ������, �.�. ��� �� ���������; // _asm �� �������������� ��� �����. �������� �������� ���������� _dbl ������, �.�. ��� mutable.
			// ReSharper disable once CppDeclaratorNeverUsed
			auto j = a;
			// ReSharper disable once CppDeclaratorNeverUsed
			auto k = b;
		};

		// ���� �������� "*this", �� ����� ��������� ����� � ��� �������� ����� �����������. ��������� ������� ����� �� ����� �������� ������. �������� "a" ������������ ��� ������ �� ������� ���� �������, �������� "b" ������ ����������.
		MyFunc = [this, &a, b]() // ������������� ��������� �� �������. ������������ ���������� � ������ �� ���������. ������������� ���� ��������� �� ������� �� ��������� � ������ �������� ����������� ����������, �.�. ��� ����� �������� � ��������.
		{
			// ReSharper disable once CppDeclaratorNeverUsed
			auto e = _dbl; // ������������ "a" ������ �� � ����� ������, �.�. ��� �� ���������; // _asm �� �������������� ��� �����. �������� �������� ���������� _dbl �����, �.�. this - ���������.
			// ReSharper disable once CppDeclaratorNeverUsed
			auto j = a;
			// ReSharper disable once CppDeclaratorNeverUsed
			auto k = b;
		};

		const auto s = [&, a]() // ��-�� [&, a] �� ���������� ������� ����� ��������� �� �������.
		{
			b = 13; // �� ������. �������� ��� ����� ����, ���� ��� mutable.
			// a++; �������� "a" ������. ��� mutable.
			// ReSharper disable once CppDeclaratorNeverUsed
			int z = a; // ������ "a" �����.
			_dbl = 0.5; // �������� _dbl ���������.
		};

		auto q = [=, &a]() mutable // ��-�� [&, a] �� ���������� ������� ����� ��������� �� �������. ������ ������� "const auto", ����� ������ ����� ������� �������.
		{
			b = 13; // �� ��������. ��� ����� �������� ��-�� mutable.
			a++; // �������� "a" �����.
			// ReSharper disable once CppDeclaratorNeverUsed
			int z = a; // ������ "a" �����.
			_dbl = 8.0; // �������� _dbl ���������.
		};

		//const auto o = [&, &a]() mutable { }; // ��-�� [&, a] �� ���������� ������� ����� ��������� �� �������. ��� ������ ������ ��-�� ����, ��� ������ �� ��������� ������������� &a. ��������� � [] �� ����� �����������.
		//const auto o = [=,  a]() mutable { }; // ��-�� [&, a] �� ���������� ������� ����� ��������� �� �������. ��� ������ ������ ��-�� ����, ��� ����� ������ ��������� � �����������. (�� �� �������, ��� � ����). ��������� � [] �� ����� �����������.

		const auto w = [this]() // ���� ������ this, �� _dbl �� ��������� ��������. ���������� _dbl ����� �������� ������ ���. �������� ���������� ������ ��������� ����� ������.
		{
			_dbl = 9.0; // �������� _dbl ���������, �������� �� ��, ��� ��� mutable.
		};

		auto df = [*this]() mutable // ���� ������ this, �� _dbl �� ��������� ��������. ���������� _dbl ����� �������� ������ ���. �������� ���������� ������ ��������� ����� ������. ����� C++17. ���� ������ mutable, �������� _dbl ����� ������.
		{
			_dbl = 19.0; // �������� _dbl �� ���������. ����� 20.1. THIS ����� ��������� ������, � ������� "=".
		};

		const auto m = [ptr = move(13), k = 0]()  // NOLINT(hicpp-move-const-arg, performance-move-const-arg)
		{
			// use ptr
			// ReSharper disable once CppDeclaratorNeverUsed
			remove_reference<int>::type io = ptr;
			// ReSharper disable once CppDeclaratorNeverUsed
			int ik = k + 1; // k++; �������� ������, �.�. ��� mutable.
		};

		unique_ptr<LambdaTest> pNum(new LambdaTest());
		const auto ttt = [ptr = move(pNum)]()
		{
			cout << "unique_ptr-> " << ptr->_dbl; // ����������� 1.1. ��������� ����� ������� � ptr, ������ ����������� �� pNum.
		};

		const auto testy = [](auto first, auto second) // ������������� ��� ������. ������ � ������ ������������ ������. ��������� ��� ������������� �������� ������. ��������� ���� ����������� �������� �����.
		{
			return first + second;
		};

		const auto testz = [] // ������������� ��� ������. ������ � ������ ������������ ������. ������ ������ ����� ��������.
		{
			return 5;
		};

		int x = 4;
		// ReSharper disable once CppDeclaratorNeverUsed
		auto yp = [&r = x, // r - ������ �� x. � [] ������ ��������� ����. ����� ������ ���������� ����� ����������: [=](auto&& ... ts).
			x = x + 1 // ������ x �� �������� (�������� �� r).
		]()->int {
			r += 2;
			return x + 2;
		}();  // ��������� ::x �� 6, � �������������� yp 7-���.

		const auto vglambda = [](auto printer) {
			return [=](auto&& ... ts) {   // OK: ts - ��� ����������� ��������� �������
				printer(std::forward<decltype(ts)>(ts)...);
			};
		};
		const auto p = vglambda([](auto v1, auto v2, auto v3, auto v4)
		{ std::cout << v1 << v2 << v3 << typeid(v4).name(); });
		p(1, 'a', 3.14, 5.25f);  // OK: ������� 1a3.14

		MyFuncZ();
		MyFunc();

		f();
		d();
		h();
		s();
		q();
		w();
		F<int, float>(1, 2.2f);
		cout << endl;
		m();
		df();
		ttt();
		// ReSharper disable once CppDeclaratorNeverUsed
		auto db = testy(9, 9.0);
		// ReSharper disable once CppDeclaratorNeverUsed
		auto ii = testz();
		Ff();

		// ��������� ������. timestwoplusthree = 13.
		// ReSharper disable once CppDeclaratorNeverUsed
		const int timestwoplusthree = [](const int x) // ���������� � ���������� 5.
		{
			return [](const int y) // ��������� ������.
			{
				return y * 2; // ���������� 10.
			}
				(x) // 5 ��� ����.
				+3; // ���������� 13.
		}(5);

		// The following code declares a lambda expression that returns
		// another lambda expression that adds two numbers.
		// The returned lambda expression captures parameter x by value.
		const auto addtwointegers = [](const int x) -> function<int(int)> {
			return [=](const int y) { return x + y; };
		};

		// The following code declares a lambda expression that takes another
		// lambda expression as its argument.
		// The lambda expression applies the argument z to the function f
		// and multiplies by 2.
		const auto higherorder = [](const function<int(int)>& fm, const int z) {
			return fm(z) * 2;
		};

		// Call the lambda expression that is bound to higherorder.
		const auto answer = higherorder(addtwointegers(7), 8);

		// Print the result, which is (7+8)*2.
		cout << answer << endl;
	}

	template<typename T> void F1(const T value)
	{
		_dbl += 11.1;
		cout << "End recursion -> Typename -> " << typeid(value).name() << " -> Value -> " << value << endl << "_dbl = " << _dbl << endl;
	}

	template<typename... T, typename E> void F1(E v, const T... values)
	{
		_dbl += 11.1;
		cout << "Typename -> " << typeid(v).name() << " -> Value -> " << v << endl << "_dbl = " << _dbl << endl;
		F1(values...);
	}

	template<typename... Args> void F(Args... args)
	{
		auto x = [this, args...] // ��� this �������� �� �����.
		{
			_dbl += 11.1; // ���������� �������� ���������� ������. ���������� 20.1.
			F1(args...);
		};
		x();
	}
};

template<typename T> void Tfunc(const T& value)
{
	cout << "End recursion -> Typename -> " << typeid(value).name() << " -> Value -> " << value << endl;
}

template<typename First, typename... Rest> void Tfunc(const First& first, Rest&... args)
{
	constexpr auto numArgs{ sizeof...(args) }; // ������� 3 ���������. ���: unsigned int.

	// ReSharper disable once CppEntityAssignedButNoRead
	First xobj[numArgs]; // ���� ��������� Rest, �� ����� ������ � �����������... ��� ���� ������ �������. ��� �� ����� ����������������.
	cout << "First -> Typename -> " << typeid(First).name() << " -> Value -> " << first << endl;
	xobj[0] = 88;
	//xobj[1] = 89; // ��������� �������� ������ ���� �������, �.�. ��� ������� �� ������� �������.
	//xobj[2] = 90;
	//First f = xobj[0]; // ���� ������, �� ����� ���������: ����������� ���������� ������ �� ��������� ������ ������� "void Tfunc<int,int,float,double>(const First &,int &,float &,double &)".

	cout << "Args count = " << numArgs << endl;
	Tfunc(args...);
}

constexpr int Increment(int n)
{
	return [n] { return n + 1; }();
}

template <typename T> void NegateAll(vector<T>& v)
{
	for_each(v.begin(), v.end(), [](T& n) { n = -n; });
}

inline void ExceptionDemo()
{
	// Create a vector that contains 3 elements.
	vector<int> elements(3);

	// Create another vector that contains index values.
	vector<int> indices(3);
	indices[0] = 0;
	indices[1] = -1; // This is not a valid subscript. It will trigger an exception.
	indices[2] = 2;

	// Use the values from the vector of index values to
	// fill the elements vector. This example uses a
	// try/catch block to handle invalid access to the
	// elements vector.
	try
	{
		for_each(indices.begin(), indices.end(), [&](const int index)
		{
			try
			{
				elements.at(index) = index;
			}
			catch (...)
			{
				throw; // ����� ���������� ���������� ������ ������, � ����� �������.
			}
		});
	}
	catch (const out_of_range& e)
	{
		cerr << "Caught '" << e.what() << "'." << endl;
	}
}

inline void LambdaPointerDemo()
{
	int y = 32, z = 33;
	float fl = 5.67f;
	double dbl = 9.89;
	Tfunc(y, z, fl, dbl);
	cout << endl;

	const auto answer = [y]() constexpr // C++17
	{
		const int x = 10;
		return y + x;
	};

	// ReSharper disable once CppDeclaratorNeverUsed
	int yu = answer(); // 42
	// ReSharper disable once CppDeclaratorNeverUsed
	int op = Increment(1); // �������� � � ����������.

	vector<int> v(10);
	vector<int>&& sv = move(v); // "v" ���������� �� �����! sv � v ����� ��������� �� ���� � ��� �� ������!! ��� ����� �� ������!!!
	// vector<int>& gv = move(v); // ��� ������������� ���������� Microsoft.
	sv[0]++;
	v[0]++;
	FillVectorExample(v);

	auto* lt = new LambdaTest;
	lt->LambdaPointerDemo();
	const Func funcZ = lt->MyFuncZ, func = lt->MyFunc;
	delete lt;
	funcZ();
	func(); // ����� ��������, �� �������� ������������� ���������.

	NegateAll(v);
	ExceptionDemo();
}