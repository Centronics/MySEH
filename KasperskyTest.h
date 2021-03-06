#pragma once
#include <unordered_map>
#include <map>
#include <vector>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

inline bool GetOne(const int value, int& pos, int& oStep)
{
	oStep = 0;
	while (pos != 0)
	{
		if ((value & pos) != 0)
			return true;
		++oStep;
		pos <<= 1;
	}
	return false;
}

int solution(int N)
{
	int maxCount = 0, pos = 1, stepCount = 0;
	while (pos != 0)
	{
		const bool t = (N & pos) != 0;
		pos <<= 1;
		if (t && GetOne(N, pos, stepCount) && stepCount > maxCount)
			maxCount = stepCount;
	}
	return maxCount;
}

void Rotate(vector<int>& v)
{
	if (v.size() < 2)
		return;
	const int lastElement = v[v.size() - 1];
	int curElement = v[v.size() - 2];
	for (vector<int>::size_type k = v.size() - 1; k > 1; --k)
	{
		v[k] = curElement;
		curElement = v[k - 2];
	}
	v[1] = curElement;
	v[0] = lastElement;
}

vector<int> solution(vector<int> &A, int K)
{
	if (A.size() < 2 || K < 1)
		return A;
	vector<int> result = A;
	for (int k = 0; k < K; ++k)
		Rotate(result);
	return result;
}

int solution(vector<int> &A)
{
	unordered_map<int, int> m;
	for (const auto& i : A)
		++m[i];

	for (const auto& p : m)
		if ((p.second % 2) != 0)
			return p.first;
	throw;
}

int solution1(vector<int> &A)
{
	if (A.empty())
		return -1;

	if (A.size() < 2)
		return 0;

	struct Value
	{
		int IValue = 0;
		vector<int>::size_type Index = -1;

		bool operator == (const Value& value) const noexcept
		{
			return IValue == value.IValue;
		}
	};

	struct MyHashFunction
	{
		size_t operator()(const Value& p) const
		{
			return p.IValue;
		}
	};

	unordered_map<Value, vector<int>::size_type, MyHashFunction> m;
	for (vector<int>::size_type k = 0; k < A.size(); ++k)
	{
		Value value{ A[k], k };
		++m[value];
	}

	pair<Value, vector<int>::size_type> maxPair; bool two = false;
	for (const auto& p : m)
	{
		if (p.second > maxPair.second)
		{
			maxPair = p;
			two = false;
			continue;
		}
		if (p.second == maxPair.second)
			two = true;
	}

	if (two)
		return -1;

	const vector<int>::size_type iHalf = A.size() / 2U;
	return (maxPair.second > iHalf) ? static_cast<int>(maxPair.first.Index) : -1;
}

int solution2(vector<int> &A) // ������� solution2, solution3, StockPicker(arr), �.�. (solution4) - ��� ������ MaxProfit � ����� codility.com.
{
	if (A.size() < 2)
		return 0;

	int min = INT_MAX, profit = 0;
	vector<int>::size_type minIndex = -1, k = 0;
	for (vector<int>::const_iterator it = A.cbegin(); it != A.cend(); ++it, ++k)
	{
		if (min < *it)
			continue;
		min = *it;
		minIndex = k;
	}

	if (minIndex == A.size() - 1)
		return 0;

	vector<int>::size_type maxIndex = A.size() - 1;
	do
	{
		const int pf = A[maxIndex] - A[minIndex];
		if (pf > profit)
			profit = pf;
		if (maxIndex-- == minIndex)
			break;
	} while (true);

	/*map<int, int> m;
	auto iter = A.cbegin();
	for (vector<int>::size_type n = 0, sz = A.size(); n < sz; ++n)
		m[*iter++] = n;

	const pair<int, int> vStart = { *A.crbegin(), A.size() - 1 };
	for (auto it = m.cbegin(); it != m.cend(); ++it)
		if (const int sum = vStart.first - it->first; sum > 0)
			return sum;*/

	return profit;
}

int solution3(vector<int>& A) // �������� 100%, �� �� ����������
{
	if (A.size() < 2)
		return 0;
	vector<int>::size_type ik = A.size() - 1;
	int result = 0;
	do
	{
		vector<int>::size_type k = ik;
		const int cMax = A[k--];
		do
		{
			const int sum = cMax - A[k];
			if (sum > result)
				result = sum;
			if (k-- == 0)
				break;
		} while (true);
		if (--ik == 0)
			break;
	} while (true);
	return result;
}

int FindMax(const vector<int>& A, const vector<int>::size_type indexMax, const vector<int>::size_type indexMin)
{
	int minDown = INT_MAX, maxUp = 0;
	vector<int>::size_type k = indexMin - 1;
	vector<int>::size_type ik = indexMax + 1;
	vector<int>::size_type dIndex = INT_MIN, uIndex = INT_MIN;
	const vector<int>::size_type sz = A.size() - 1;
	bool o1End = false, o2End = false;
	if (ik >= sz)
	{
		o1End = true;
		maxUp = A[ik];
		uIndex = ik;
	}
	if (indexMin == 0)
	{
		o2End = true;
		minDown = A[k];
		dIndex = k;
	}
	do
	{
		if (!o1End)
		{
			const int value = A[ik];
			if (value > maxUp)
			{
				maxUp = value;
				uIndex = ik;
			}
			if (ik < sz)
				++ik;
			else
				o1End = true;
		}
		if (!o2End)
		{
			const int value = A[k];
			if (value < minDown)
			{
				minDown = value;
				dIndex = k;
			}
			if (k > 0)
				--k;
			else
				o2End = true;
		}
	} while (!o1End || !o2End);

	const int value1 = A[uIndex] - A[dIndex];
	const int value2 = A[uIndex] - A[indexMin];
	const int value3 = A[indexMax] - A[dIndex];
	int maxVal = value1 < value2 ? value2 : value1;
	maxVal = maxVal < value3 ? value3 : maxVal;
	if (static_cast<vector<int>::size_type>(uIndex - dIndex) == sz)
		return maxVal;
	const int val1 = FindMax(A, uIndex, dIndex);
	return val1 > maxVal ? val1 : maxVal;
}

// ������: { 23171, 21011, 21123, 21366, 21013, 21367 } ���������� ��������: 356. ��� ������ MaxProfit � ����� codility.com.
int solution5(vector<int>& A)
{
	if (A.size() < 2)
		return 0;

	int min = INT_MAX, max = 0;
	vector<int>::size_type indexMin = INT_MIN, indexMax = INT_MIN;
	const vector<int>::size_type mk = A.size() - 1;
	vector<int>::size_type k = mk;
	do
	{
		const int value = A[k];
		if (value > max)
		{
			indexMax = k;
			max = value;
		}
		if (value < min)
		{
			indexMin = k;
			min = value;
		}
		if (k-- == 0)
			break;
	} while (true);

	return indexMax < indexMin ? FindMax(A, indexMax, indexMin) : max - min;
}

/*function StockPicker(arr) {

  var max_profit = -1;
  var buy_price = 0;
  var sell_price = 0;

  // this allows our loop to keep iterating the buying
  // price until a cheap stock price is found
  var change_buy_index = true;

  // loop through list of stock prices once
  for (var i = 0; i < arr.length-1; i++) {

	// selling price is the next element in list
	sell_price = arr[i+1];

	// if we have not found a suitable cheap buying price yet
	// we set the buying price equal to the current element
	if (change_buy_index) { buy_price = arr[i]; }

	// if the selling price is less than the buying price
	// we know we cannot make a profit so we continue to the
	// next element in the list which will be the new buying price
	if (sell_price < buy_price) {
	  change_buy_index = true;
	  continue;
	}

	// if the selling price is greater than the buying price
	// we check to see if these two indices give us a better
	// profit then what we currently have
	else {
	  var temp_profit = sell_price - buy_price;
	  if (temp_profit > max_profit) { max_profit = temp_profit; }
	  change_buy_index = false;
	}

  }

  return max_profit;
}

StockPicker([44, 30, 24, 32, 35, 30, 40, 38, 15]);  */

/*int solution4(vector<int> &A) // ������� (3) ������ MaxProfit.
{
	int max_profit = -1;
	int buy_price = 0;

	// this allows our loop to keep iterating the buying
	// price until a cheap stock price is found
	bool change_buy_index = true;

	// loop through list of stock prices once
	for (vector<int>::size_type i = 0; i < A.size() - 1; ++i) {

		// selling price is the next element in list
		int sell_price = A[i + 1];

		// if we have not found a suitable cheap buying price yet
		// we set the buying price equal to the current element
		if (change_buy_index) { buy_price = A[i]; }

		// if the selling price is less than the buying price
		// we know we cannot make a profit so we continue to the
		// next element in the list which will be the new buying price
		if (sell_price < buy_price) {
			change_buy_index = true;
			continue;
		}

		// if the selling price is greater than the buying price
		// we check to see if these two indices give us a better
		// profit then what we currently have
		const int temp_profit = sell_price - buy_price;
		if (temp_profit > max_profit) { max_profit = temp_profit; }
		change_buy_index = false;
	}

	return max_profit;
}
*/

// ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
struct Base
{
	virtual void Foo() { cout << "BASE:Foo" << endl; }
};

// ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
struct Derived : Base
{
	virtual void Foo(int i = 0) { cout << "derived::FOO" << endl; }  // NOLINT(clang-diagnostic-overloaded-virtual)
};

/*
 *������:
Derived d;
d.Foo();
Base &b = d;
b.Foo();
*/