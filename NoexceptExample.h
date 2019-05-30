#pragma once
#include <cstdlib>

using namespace std;

inline void NoexceptExample1() noexcept
{
	throw 5;
}

inline void NoexceptExample2() noexcept(true)
{
	throw 5;
}

inline void NoexceptExample3() noexcept(false)
{
	throw 5;
}

inline void AbortDemo() noexcept
{
	abort();
}

inline void NoexceptDemo() noexcept
{
	try
	{
		//NoexceptExample1();
		//NoexceptExample2();
		//NoexceptExample3();
		AbortDemo();
	}
	catch (...)
	{
		throw;
	}
}