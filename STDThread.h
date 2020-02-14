#pragma once

#include <thread>

using namespace std;

inline void STDThreadDemo()
{
	int a = 0;

	thread t1([&] { a++; });

	thread t2([&] { ++a; });

	thread t3([&] { a = a + 1; });

	__asm nop;
}