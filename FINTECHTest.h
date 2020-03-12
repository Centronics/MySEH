#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

inline void FileReader()
{
	ifstream file(L"D:\\file.txt");
	if (!file)
		return;
	map<string, unsigned> mp;
	while (!file.eof())
	{
		string str;
		file >> str;
		if (str.empty())
			continue;
		++mp[str];
	}
	file.close();
	multimap<unsigned, string> mm;
	for (pair<string, unsigned> p : mp)
		mm.insert(pair<unsigned, string>(p.second, p.first));
	for (auto k = mm.crbegin(); k != mm.crend(); ++k)
		cout << k->second << ' ' << k->first << " times" << endl;
}