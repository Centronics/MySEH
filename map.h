#pragma once
#include <map>

using namespace std;

class BigClass
{
public:
	unsigned char cr[524288];//000]; // не хватит размера кучи
};

void vd(int& i){}

inline void MultiMapTest()
{
	int u;
	vd(u);
	multimap<int, char> mm;
	mm.insert(pair<int, char>(10, 'a'));
	mm.insert(pair<int, char>(10, 'a'));
	mm.insert(pair<int, char>(13, 'a'));
	auto mb = mm.insert(pair<int, char>(15, 'b'));
	multimap<int, char>::iterator i = mm.find(10);//только ключ
	auto t1 = i->first;
	auto t2 = i->second;
	i->second = 'c'; // только значение можно менять (second)
	//*i=180;//pair<int, char>(180, 'a');
	auto f1 = mm.lower_bound(10);
	auto f2 = mm.upper_bound(10);
	mm.erase(10);
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
}