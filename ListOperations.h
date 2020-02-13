#pragma once

#include <list>
#include <vector>

using namespace std;

template <typename T> void ListOperationsDemo()
{
	T lst = { 1, 2, 3, 4, 5 };
	for (auto it = lst.begin(); it != lst.end(); ++it)
	{
		if (*it < 3)
			continue;
		const auto iter = it++;
		lst.erase(iter);
		--it;
	}
}

/*
 *ListOperationsDemo<list<int>>();
ListOperationsDemo<vector<int>>(); // �� ���������, � vector ����� ������ �� ������ 17.
*/