#pragma once
#include <map>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BigClass
{
public:
	unsigned char cr[524288];//000]; // не хватит размера кучи
};

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

void vd(int& i) {}

inline void MultiMapTest()
{
	int u;
	vd(u);
	multimap<int, char> mm;
	mm.insert(pair<int, char>(10, 'a'));
	mm.insert(pair<int, char>(10, 'a'));
	mm.insert(pair<int, char>(10, 'a'));
	mm.insert(pair<int, char>(13, 'a'));
	auto mb = mm.insert(pair<int, char>(15, 'b'));
	multimap<int, char>::iterator i = mm.find(10);//только ключ
	auto t1 = i->first;
	auto t2 = i->second;
	i->second = 'c'; // только значение можно менять (second)
	//*i=180;//pair<int, char>(180, 'a');

	// перечисляем все элементы
	/*for(auto& e : mm) // поменяет все на s
	{
		e.second = 's';
		//e.first = 10; // писать нельзя
	}*/

	auto f1 = mm.lower_bound(10); // нижний диапазон
	auto f2 = mm.upper_bound(10); // верхний диапазон
	mm.erase(f1);
	mm.erase(f2);
	mm.erase(10); // удалит все элементы с ключами 10
	mm.erase(mb);
}

inline void MapTest()
{
	MultiMapTest();

	map<int, BigClass> bg; // можно
	const size_t sz = sizeof(map<int, BigClass>);

	map<char*, int> mp;
	mp.insert(std::pair<char*, int>("a", 100)); // не может вставить, если такой уже есть
	mp.insert(std::pair<char*, int>("a", 102));
	mp.insert(std::pair<char*, int>("b", 101));

	map<void*, int> mp1;
	int i, i1;
	mp1.insert(std::pair<void*, int>(&i, 100));
	mp1.insert(std::pair<void*, int>(&i1, 100));

	map<string, int> test_map;
	test_map["ten"] = 10; // изменяет существующий
	test_map["ten"] = 8;
	test_map["ten"] = 9;

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

	MyMap mp2 = { 1, 2, 3 };
	MyMap op = 9; // explicit даёт здесь ошибку. При нём надо писать static_cast<MyMap>(9).
	MyMap(6.7f, 23);

	initializer_list<float> el(nullptr, nullptr);

	// ЗАДАЧА по нахождению дубликатов
	
	vector<string> names = { "photo", "photo(1)", "photo", "doc", "photo(1)", "photo(2)", "photo" }; // {"photo", "photo", "doc", "photo(1)", "photo"}; // изначальный

	map<string, int> libNames;
	for (auto& t : names)
	{
		const string ct = t;
		auto e = libNames[t];
		if (e > 0)
		{
			t += '(';
			t += to_string(e);
			t += ')';
			libNames[t] = e;
		}
		++e;
		libNames[ct] = e;
	}
}