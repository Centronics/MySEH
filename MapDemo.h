#pragma once
#include <iostream>
#include <map>
#include <string>

using namespace std;

class MyMap
{
public:
	MyMap(const initializer_list<int>& elems)
	{

	}

	MyMap(int i)
	{

	}

	MyMap(float, int)
	{

	}
};

inline void MapDemo()
{
	map<string, size_t> albums = {
		{"Coven", 1991},
		{"Fool", 1997}
	};

	auto[position, inserted] = albums.emplace("Outcast", 2005);
	for (const auto&[name, year] : albums)
		cout << name << ": " << year << "\n";

	MyMap mp = { 1, 2, 3 };
	MyMap op = 9; // explicit даёт здесь ошибку. При нём надо писать (9).
	MyMap(6.7f, 23);

	initializer_list<float> el(0, 0);
}