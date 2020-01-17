#pragma once
#include <vector>
#include <chrono>
#include <iostream>
#include <deque>

using namespace std;
using namespace std::chrono;

class A
{

};

class B
{

};

class Foo {  // NOLINT(hicpp-special-member-functions)
public:
	Foo(A* a, B* b) : a_(a), b_(b) {}

	Foo(const Foo& foo) : a_(nullptr), b_(nullptr)
	{
		try
		{
			if (foo.a_ != nullptr)
				a_ = new A(*foo.a_);

			if (foo.b_ != nullptr)
				b_ = new B(*foo.b_);
		}
		catch (...)
		{
			delete a_;
			delete b_;
			throw;
		}
	}

	~Foo() {
		delete a_;
		delete b_;
	}

	// Write the copy constructor for the class Foo. 
	// Ownership of a and b should be maintained by Foo.
	// Types A and B are copy-constructible.

private:
	A* a_;
	B* b_;
};

///////////////////////////////////////////////////////////////////////////////////////////

// 0 0 0 0 0 0 1 1 1 1 1 1 1
//           0 0 0 0 0 0 1 0 1 0 1 0 1
//           0 0 0 0 0 0 0 0 1 0 1 0 1
//           1 1 1 1 1 1 1 1 1 1 1 1 1
// 1 1 1 1 1 1 1 1 1 1 1 1 1

//  0 0 0 0 0 0 0 2 2 2 2 2


// 1 1 1 1

// 1 1 1 1 1 1 1 

/*inline bool VectorCompare(const vector<int>& v1, const vector<int>& v2)
{
	if (v1.size() != v2.size())
		return false;
	for (vector<int>::size_type k = 0; k < v1.size(); ++k)
		if (v1[k] != v2[k])
			return false;
	return true;
}*/

inline bool VerifyResult(const vector<int>& v)
{
	for (const int k : v)
		if (k == 0)
			return false;
	return true;
}

class VectorGenerator
{
public:
	VectorGenerator(const size_t masLen, const int nonZeroValue) : _signVector(masLen), _masLen(masLen), _nonZeroValue(nonZeroValue)
	{
		if (nonZeroValue == 0)
			throw;
	}

private:
	vector<int> _signVector;
	size_t _masLen;
	vector<int> _generated;
	bool _firstGenerated = false;
	const int _nonZeroValue;

	void Generate()
	{
		if (_masLen == 0)
		{
			_generated = vector<int>();
			return;
		}

		const auto incCounter = [this]
		{
			if (!_firstGenerated)
			{
				_firstGenerated = true;
				return true;
			}
			vector<int>::size_type k = _signVector.size();
			while (k--)
				if (int* t = &_signVector[k]; *t < _nonZeroValue)
				{
					++(*t);
					return true;
				}
				else
				{
					if (k == 0)
						return false;
					int* lastElement = &_signVector[0] + _signVector.size();
					memset(t, 0, (lastElement - t) * sizeof(int));
					++(*t);
					return true;
				}
			return false;
		};

		if (!incCounter())
		{
			_generated = vector<int>();
			return;
		}

		vector<int> t(_masLen);
		vector<int>::size_type nonZeroCount = 0;
		for (vector<int>::size_type k = 0; k < _signVector.size(); ++k)
			if (_signVector[k])
			{
				t[k] = _nonZeroValue;
				++nonZeroCount;
			}

		_generated = move(t);
	}

public:
	[[nodiscard]] vector<int>* begin()
	{
		Generate();
		if (_generated.empty())
			return nullptr;
		return &_generated;
	}

	// ReSharper disable once CppMemberFunctionMayBeStatic
	// ReSharper disable once CppInconsistentNaming
	[[nodiscard]] vector<int>* end()
	{
		return nullptr;
	}
};

inline vector<tuple<bool, long long, vector<int>>> RemoveZero(vector<int>& v)
{
	//for (vector<int>::size_type k = v.size() - 1; k >= 0; --k) // ОРИГИНАЛ
	//{
	//	if (v[k] == 1)
	//	{
	//		v[k] = 0;
	//		for (vector<int>::size_type i = 0; i < v.size(); ++i)
	//		{
	//			if (v[i] == 0)
	//			{
	//				v[i] = 1;
	//				break;
	//			}
	//		}
	//	}
	//}

	auto solSobesOrig = [v]()mutable -> tuple<bool, long long, vector<int>>
	{
		const steady_clock::time_point start = steady_clock::now();
		for (vector<int>::size_type k = v.size() - 1; k >= 0; --k) // ОРИГИНАЛ
		{
			if (v[k] == 1)
			{
				v[k] = 0;
				for (vector<int>::size_type i = 0; i < v.size(); ++i)  // NOLINT(modernize-loop-convert)
				{
					if (v[i] == 0)
					{
						v[i] = 1;
						break;
					}
				}
			}
			if (k == 0)
				break;
		}
		const steady_clock::time_point end = steady_clock::now();
		return make_tuple(true, duration_cast<microseconds>(end - start).count(), v);
	};

	auto solNonOpt = [v]() mutable -> tuple<bool, long long, vector<int>>
	{
		const steady_clock::time_point start = steady_clock::now();
		vector<int>::size_type k = 0;
		for (auto begin = v.begin(); begin != v.end(); ++begin, ++k)
			if (*begin == 0)
			{
				v.erase(begin); // После этого итератор недействителен.
				--k;
				begin = v.begin() + k;
			}
		const steady_clock::time_point end = steady_clock::now();
		return make_tuple(true, duration_cast<microseconds>(end - start).count(), v);
	};

	auto solSobes = [v]() mutable->tuple<bool, long long, vector<int>>
	{
		if (v.size() < 2)
			return tuple<bool, long long, vector<int>>();
		const steady_clock::time_point start = steady_clock::now();
		vector<int>::size_type lastZero = -1;
		vector<int>::size_type k = v.size() - 1;
		do
		{
			if (v[k] == 0)
				continue;
			v[k] = 0;
			for (vector<int>::size_type i = lastZero + 1; i < v.size(); ++i)
				if (v[i] == 0)
				{
					v[i] = 1;
					lastZero = i;
					break;
				}
			if (k == 0 || k <= (lastZero + 2))
				break;
		} while (--k);
		v.resize(lastZero + 1);
		const steady_clock::time_point end = steady_clock::now();
		return make_tuple(true, duration_cast<microseconds>(end - start).count(), v);
	};

	const auto nonOpt = solNonOpt();
	const auto sobes = solSobes();
	const auto sobesOrig = solSobesOrig();

	const bool b = get<0>(nonOpt);
	if (b != get<0>(sobes) || b != get<0>(sobesOrig))
		throw;

	if (!VerifyResult(get<2>(nonOpt)) || !VerifyResult(get<2>(sobes)) || !VerifyResult(get<2>(sobesOrig)))
		throw;

	vector<tuple<bool, long long, vector<int>>> result;
	result.emplace_back(nonOpt);
	result.emplace_back(sobes);
	result.emplace_back(sobesOrig);
	return result;
}

inline void YandexTest()
{
	{
		A* pa = new A();
		B* pb = new B();
		const Foo f(pa, pb);
		// ReSharper disable once CppDeclaratorNeverUsed
		const Foo& d(f);
		//_asm int 3;
	}

	{
		deque<tuple<bool, long long, vector<int>>> d;
		VectorGenerator vc(3, 1);
		for (vector<int>& v : vc)
			for (auto& r : RemoveZero(v))
				d.emplace_back(move(r));
		_asm int 3;
	}
}