#pragma once
#include <vector>
#include <algorithm>

using namespace std;

inline void ForEachDemo()
{
	vector<int> vec(10);
	int a = 1;
	for_each(vec.begin(), vec.end(), [a](int& n) mutable // ��������� "a" ��������, ��������� ���������� ���� ��������� �� ����. ���� � ���, ��� ���������� "a" ���������� �� ��������� ������� ������.
	{
		n = a++;
	});
	// a = 1;
	for_each(vec.begin(), vec.end(), [&a](int& n) // �������� ��������� ����������. ��������� "a" �� �������� 20.
	{
		a = n * 2;
		n = a; // ���� �������� "a++", �� �������� ��������� �������� �� �����.
	});
	// a = 20;
	for_each(vec.begin(), vec.end(), [](int n) // �������� ��������� �� ����������.
	{
		n++;
	});
}