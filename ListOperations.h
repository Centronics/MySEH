#pragma once

#include <list>

using namespace std;

inline void ListOperationsDemo()
{
	list<int> lst = { 1, 2, 3, 4, 5 };
	for (auto it = lst.begin(); it != lst.end(); ++it)
	{
		if (*it < 3)
			continue;
		const auto iter = it++;
		lst.erase(iter);
		--it;
	}
}