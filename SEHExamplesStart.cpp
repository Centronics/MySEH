/*#include "ExampleOne.h"
#include "Example2.h"
#include "Example3.h"
#include "VirtualDestructor.h"
#include "VirtualInheriting.h"
#include "Example4.h"
#include "Example5.h"
#include "DestrException.h"
#include "ConstrException.h"
#include "Example6.h"
#include "LinkExample.h"
#include "DestrException2.h"
#include "Example7.h"
#include "IsVirtual.h"
#include "Overload.h"
#include "VurtualFuncInCtr.h"
#include "Example8.h"
#include "Access.h"
#include "Construction.h"
#include "CopyConstructor.h"
#include "typedefMas.h"
#include "ClassCopy.h"
#include "UniquePtr.h"
#include "PointerFromReference.h"
#include "DefaultConstructor.h"
#include "LambdaPointer.h"
#include "MoveConstructor.h"
#include "NoexceptExample.h"
#include "ProtectedConstructor.h"
#include "OperatorInheriting.h"
#include "ForEach.h"
#include "Alignas.h"
#include "Relatives.h"
#include "MapDemo.h"
#include "Decltype.h"
#include "Expression.h"
#include "FormatString.h"
#include "Template.h"
#include "StaticIntTest.h"
#include "DynamicTemplate.h"
#include "Switch.h"
#include "Any.h"
#include "Union.h"
#include "Equal.h"
#include "Narrow.h"
#include "Inheriting.h"
#include "KeepWindowOpen.h"
#include "Initialization.h"
#include "SobesErrors_31_07_2015.h"
#include "Explicit.h"
#include "VariableArguments.h"
#include "PlacementNew.h"
#include "Defaults.h"
#include "Casting.h"
#include "map.h"
#include "YandexSobesTest.h"
#include "ListOperations.h"
#include "STDThread.h"*/

/*#include <unordered_map>
//#include <map>

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

#include <list>

#include <vector>

using namespace std;

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
*/

#include <vector>
#include <map>
#include <climits>
#include <iostream>

using namespace std;

int solution2(vector<int> &A) // РЕШЕНИЯ solution2, solution3, StockPicker(arr), т.е. (solution4) - это задача MaxProfit с сайта codility.com.
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

int solution3(vector<int>& A) // РАБОТАЕТ 100%, но не оптимально
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

tuple<int, int> FindMax(const vector<int>& A, const vector<int>::size_type indexMin, const vector<int>::size_type indexMax)
{
	int minDown = INT_MAX, maxUp = 0;
	vector<int>::size_type k = indexMax;
	vector<int>::size_type ik = indexMin;
	int dIndex = INT_MIN, uIndex = INT_MIN;
	bool o1End = false, o2End = false;
	const vector<int>::size_type sz = A.size() - 1;
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

	if (static_cast<vector<int>::size_type>(uIndex - dIndex) != A.size())
		return make_tuple(minDown, maxUp);//сравнить значения свои с возвращенными
	return FindMax(A, uIndex, dIndex);
}

int solution5(vector<int>& A)
{
	if (A.size() < 2)
		return 0;

	int min = INT_MAX, max = 0;
	vector<int>::size_type indexMin = INT_MIN, indexMax = INT_MIN;
	vector<int>::size_type k = A.size() - 1;
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

	if (indexMax >= indexMin)
		return max - min;

	auto dp = FindMax(A, indexMin, indexMax);
	const int preSumm1 = max - get<0>(dp), preSumm2 = get<1>(dp) - min;
	return preSumm1 > preSumm2 ? preSumm1 : preSumm2;
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

int solution4(vector<int> &A) // Решение 3 задачи MaxProfit.
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



struct Base
{
	virtual void Foo() { cout << "BASE:Foo" << endl; }
};

struct Derived : Base
{
	virtual void Foo(int i = 0) { cout << "derived::FOO" << endl; }
};

#include "KasperskyProblemTest.h"

int __cdecl main()
{
	try
	{
		vector<int> iv = {1};
		iv.erase(iv.begin(),iv.begin());
		
		vector<string> strings = { "D:\\123.txt", "F:\\124.txt", "G:123.tyt" };
		auto v = solution(strings);
		
		/*Derived d;
		d.Foo();
		Base &b = d;
		b.Foo();

		vector<int> v = { 23171, 21011, 21123, 21366, 21013, 21367 }; //{ 23171, 21011, 21123, 21366, 21013, 21367 }; //356 //{ 1,2,3,4,5 };//5,1,2,3,4
		// v.emplace_back(); // Добавит 0, т.е. вызовет конструктор по умолчанию.
		// ReSharper disable once CppDeclaratorNeverUsed
		auto t = solution5(v);

		// ReSharper disable once CppDeclaratorNeverUsed
		//int i = solution(2'147'483'647);*/
		return 0;
	}
	catch (...)
	{
		return 1;
	}
}