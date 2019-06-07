#pragma once
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <typeinfo>
#include <functional>

using namespace std;
using Func = function<void()>;

inline void FillVectorExample(vector<int>& v) // Если здесь была бы ссылка, то вызов с аргументом vector<int>() привёл бы к предупреждению о том, что это нестандартное расширение Microsoft.
{
	// A local static variable.
	static int nextValue = 1;

	// The lambda expression that appears in the following call to
	// the generate function modifies and uses the local static
	// variable nextValue.
	generate(v.begin(), v.end(), [] { return nextValue++; }); // Заполнит массив от 1 до 10.
	//WARNING: this is not thread-safe and is shown for illustration only
}

class LambdaTest
{
	double _dbl = 1.1;

public:
	Func MyFuncZ, MyFunc;

	Func Ff = [] // Так тоже можно инициализоваться лямбду.
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
			int t = a; // "a" изменять нельзя.
		};

		auto d = [a, &b]() mutable noexcept -> void // mutable ограничивает только изменение переменных, переданных по значению. Значение изменяется только внутри лямбды, при этом объявить саму переменную как const нельзя. Значения, переданные по ссылкам, можно изменять всегда.
		{
			a++; // Можно изменять значения захваченных переменных из-за mutable.
			b = 12;
		};

		/*auto j = []() // НЕ УДАЛЯТЬ.
		{
			int y = a; // сослаться на "a" нельзя даже для чтения. [] - означает отсутствие захваченных переменных.
		};*/

		void(*h)() = []() // Использование указателя на функцию. Использовать соглашение о вызове не получится. Использование типа указателя на функцию не получится в случае указания захваченных переменных, т.к. это может привести к путанице.
		{
			// ReSharper disable once CppDeclaratorNeverUsed
			int e = 0; // Использовать "a" нельзя ни в каком смысле, т.к. она не захвачена; // _asm не поддерживается для лямбд.
		};

		// Если написать "*this", то будет захвачена копия и все значения будут правильными. Состояние объекта будет на время создания лямбды. Значение "a" неправильное при выходе за пределы этой функции, значение "b" всегда правильное.
		MyFuncZ = [*this, &a, b]() // Использование указателя на функцию. Использовать соглашение о вызове не получится. Использование типа указателя на функцию не получится в случае указания захваченных переменных, т.к. это может привести к путанице.
		{
			// ReSharper disable once CppDeclaratorNeverUsed
			auto e = _dbl; // Использовать "a" нельзя ни в каком смысле, т.к. она не захвачена; // _asm не поддерживается для лямбд. ИЗМЕНИТЬ значение переменной _dbl нельзя, т.к. нет mutable.
			// ReSharper disable once CppDeclaratorNeverUsed
			auto j = a;
			// ReSharper disable once CppDeclaratorNeverUsed
			auto k = b;
		};

		// Если написать "*this", то будет захвачена копия и все значения будут правильными. Состояние объекта будет на время создания лямбды. Значение "a" неправильное при выходе за пределы этой функции, значение "b" всегда правильное.
		MyFunc = [this, &a, b]() // Использование указателя на функцию. Использовать соглашение о вызове не получится. Использование типа указателя на функцию не получится в случае указания захваченных переменных, т.к. это может привести к путанице.
		{
			// ReSharper disable once CppDeclaratorNeverUsed
			auto e = _dbl; // Использовать "a" нельзя ни в каком смысле, т.к. она не захвачена; // _asm не поддерживается для лямбд. Изменить значение переменной _dbl можно, т.к. this - указатель.
			// ReSharper disable once CppDeclaratorNeverUsed
			auto j = a;
			// ReSharper disable once CppDeclaratorNeverUsed
			auto k = b;
		};

		const auto s = [&, a]() // Из-за [&, a] не получилось вызвать через указатель на функцию.
		{
			b = 13; // По ссылке. Изменять его можно даже, если нет mutable.
			// a++; Изменить "a" нельзя. Нет mutable.
			// ReSharper disable once CppDeclaratorNeverUsed
			int z = a; // Читать "a" можно.
			_dbl = 0.5; // Значение _dbl изменится.
		};

		auto q = [=, &a]() mutable // Из-за [&, a] не получилось вызвать через указатель на функцию. Нельзя ставить "const auto", иначе нельзя будет вызвать функцию.
		{
			b = 13; // По значению. Его можно изменять из-за mutable.
			a++; // Изменить "a" можно.
			// ReSharper disable once CppDeclaratorNeverUsed
			int z = a; // Читать "a" можно.
			_dbl = 8.0; // Значение _dbl изменится.
		};

		//const auto o = [&, &a]() mutable { }; // Из-за [&, a] не получилось вызвать через указатель на функцию. ТАК ПИСАТЬ НЕЛЬЗЯ из-за того, что ссылка по умолчанию соответствует &a. Аргументы в [] НЕ МОГУТ повторяться.
		//const auto o = [=,  a]() mutable { }; // Из-за [&, a] не получилось вызвать через указатель на функцию. ТАК ПИСАТЬ НЕЛЬЗЯ из-за того, что явный захват совпадает с умолчаниями. (Та же причина, что и выше). Аргументы в [] НЕ МОГУТ повторяться.

		const auto w = [this]() // Если убрать this, то _dbl не получится изменить. Переменную _dbl можно изменить только так. Значение переменной класса изменится через лямбду.
		{
			_dbl = 9.0; // Значение _dbl изменится, несмотря на то, что нет mutable.
		};

		auto df = [*this]() mutable // Если убрать this, то _dbl не получится изменить. Переменную _dbl можно изменить только так. Значение переменной класса изменится через лямбду. Фишка C++17. Если убрать mutable, изменять _dbl будет нельзя.
		{
			_dbl = 19.0; // Значение _dbl не изменится. Будет 20.1. THIS можно захватить неявно, с помощью "=".
		};

		const auto m = [ptr = move(13), k = 0]()  // NOLINT(hicpp-move-const-arg, performance-move-const-arg)
		{
			// use ptr
			// ReSharper disable once CppDeclaratorNeverUsed
			remove_reference<int>::type io = ptr;
			// ReSharper disable once CppDeclaratorNeverUsed
			int ik = k + 1; // k++; написать нельзя, т.к. нет mutable.
		};

		unique_ptr<LambdaTest> pNum(new LambdaTest());
		const auto ttt = [ptr = move(pNum)]()
		{
			cout << "unique_ptr-> " << ptr->_dbl; // Отобразится 1.1. Указатель будет сохранён в ptr, будучи перенесённым из pNum.
		};

		const auto testy = [](auto first, auto second) // Компилируется как шаблон. Шаблон в лямбде использовать нельзя. Назначить тип возвращаемого значения нельзя. Назначить типы принимаемых значений можно.
		{
			return first + second;
		};

		const auto testz = [] // Компилируется как шаблон. Шаблон в лямбде использовать нельзя. ПУСТЫЕ скобки можно опустить.
		{
			return 5;
		};

		int x = 4;
		// ReSharper disable once CppDeclaratorNeverUsed
		auto yp = [&r = x, // r - ссылка на x. В [] нельзя указывать типы. Можно делать переменное число аргументов: [=](auto&& ... ts).
			x = x + 1 // захват x по значению (отдельно от r).
		]()->int {
			r += 2;
			return x + 2;
		}();  // Обновляет ::x до 6, и инициализирует yp 7-кой.

		const auto vglambda = [](auto printer) {
			return [=](auto&& ... ts) {   // OK: ts - это упакованные параметры функции
				printer(std::forward<decltype(ts)>(ts)...);
			};
		};
		const auto p = vglambda([](auto v1, auto v2, auto v3, auto v4)
		{ std::cout << v1 << v2 << v3 << typeid(v4).name(); });
		p(1, 'a', 3.14, 5.25f);  // OK: выводит 1a3.14

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

		// ВЛОЖЕННАЯ ЛЯМБДА. timestwoplusthree = 13.
		// ReSharper disable once CppDeclaratorNeverUsed
		const int timestwoplusthree = [](const int x) // Вызывается с аргументом 5.
		{
			return [](const int y) // Вложенная лямбда.
			{
				return y * 2; // Получается 10.
			}
				(x) // 5 идёт сюда.
				+3; // Получается 13.
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
		auto x = [this, args...] // без this работать не будет.
		{
			_dbl += 11.1; // Изменяется значение переменной класса. Получается 20.1.
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
	constexpr auto numArgs{ sizeof...(args) }; // Покажет 3 аргумента. Тип: unsigned int.

	// ReSharper disable once CppEntityAssignedButNoRead
	First xobj[numArgs]; // Если поставить Rest, то будет ошибка о нераскрытии... его сюда нельзя ставить. Они не будут инициализированы.
	cout << "First -> Typename -> " << typeid(First).name() << " -> Value -> " << first << endl;
	xobj[0] = 88;
	//xobj[1] = 89; // Остальные элементы нельзя сюда ставить, т.к. они выходят за пределы массива.
	//xobj[2] = 90;
	//First f = xobj[0]; // Если убрать, то будет сообщение: выполняется компиляция ссылки на экземпляр шаблон функции "void Tfunc<int,int,float,double>(const First &,int &,float &,double &)".

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
				throw; // Можно обработать исключение внутри лямбды, а можно снаружи.
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
	int op = Increment(1); // Работает и с переменной.

	vector<int> v(10);
	vector<int>&& sv = move(v); // "v" перемещено не будет! sv и v будут указывать на один и тот же объект!! ТАК ЛУЧШЕ НЕ ПИСАТЬ!!!
	// vector<int>& gv = move(v); // Это нестандартное расширение Microsoft.
	sv[0]++;
	v[0]++;
	FillVectorExample(v);

	auto* lt = new LambdaTest;
	lt->LambdaPointerDemo();
	const Func funcZ = lt->MyFuncZ, func = lt->MyFunc;
	delete lt;
	funcZ();
	func(); // Будет работать, но возможно неопределённое поведение.

	NegateAll(v);
	ExceptionDemo();
}