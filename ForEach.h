#pragma once
#include <vector>
#include <algorithm>

using namespace std;

inline void ForEachDemo()
{
	vector<int> vec(10);
	int a = 1;
	for_each(vec.begin(), vec.end(), [a](int& n) mutable // Поскольку "a" захвачен, произойдёт увеличение всех элементов на один. Дело в том, что переменная "a" существует во временном объекте лямбды.
	{
		n = a++;
	});
	// a = 1;
	for_each(vec.begin(), vec.end(), [&a](int& n) // Значения элементов изменяются. Изменится "a" на значение 20.
	{
		a = n * 2;
		n = a; // Если написать "a++", то значение элементов меняться не будет.
	});
	// a = 20;
	for_each(vec.begin(), vec.end(), [](int n) // Значения элементов не изменяются.
	{
		n++;
	});
}