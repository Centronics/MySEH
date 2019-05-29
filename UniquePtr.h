#pragma once
#include <memory>
#include <functional>
#include <iostream>
#include <cstdio>

template<typename T>
using auto_cleanup = std::unique_ptr<T, std::function<void(T*)>>;

static char dummy[] = "";

#define _DEFER_CAT_(a,b) a##b
#define _DEFER_NAME_(a,b) _DEFER_CAT_(a,b)
#define defer(...) \
  auto _DEFER_NAME_(_defer_,__LINE__) = \
    auto_cleanup<char>(dummy, [&](char*) { __VA_ARGS__; });

void UniquePtrDemo()
{
	auto_cleanup<FILE> f(
		fopen("test.txt", "w"),
		[](FILE* f)
	{
		fclose(f);
	});

	defer(std::cout << "Bye #1" << std::endl);
	defer(std::cout << "Bye #2" << std::endl);

	fwrite("Hello!\n", 7, 1, f.get());
}