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
	/* В mm элементы будут расположены по ключу в порядке инициализации: {'a',1},{'a',4},{'a',5},{'b',2},{'c',3},{'c',1}.
	 * Инициализация m начнётся со второго элемента и закончится до первого элемента с ключём 'c'. Значит, m будет содержать {'a',4} и {'b',2}.
	 * В первом цикле изменяется копия m, то есть во втором цикле будет выведена неизменённая исходная карта.
	 * Программа выведет: 4 2. */

	multimap<char, int> mm = { {'a',1}, {'b',2}, {'c',3}, {'a',4}, {'a',5}, {'c',1} };
	map<char, int> m(++mm.begin(), mm.lower_bound('c'));
	for (auto i : m)
		++i.second;
	for (decltype(auto) i : m)
		cout << i.second << ' ';

	map<string, size_t> albums = {
		{"Coven", 1991},
		{"Fool", 1997}
	};

	auto[position, inserted] = albums.emplace("Outcast", 2005);
	for (const auto&[name, year] : albums)
		cout << name << ": " << year << "\n";

	MyMap mp = { 1, 2, 3 };
	MyMap op = 9; // explicit даёт здесь ошибку. При нём надо писать static_cast<MyMap>(9).
	MyMap(6.7f, 23);

	initializer_list<float> el(nullptr, nullptr);
}