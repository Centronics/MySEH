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

inline bool VectorCompare(const vector<int>& v1, const vector<int>& v2)
{
	if (v1.size() != v2.size())
		return false;
	for (vector<int>::size_type k = 0; k < v1.size(); ++k)
		if (v1[k] != v2[k])
			return false;
	return true;
}

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
				if (int* t = &_signVector[k]; *t == 0)
				{
					*t = _nonZeroValue;
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

struct Result
{
	tuple<bool, long long, vector<int>> NonOpt;
	tuple<bool, long long, vector<int>> Sobes;
	tuple<bool, long long, vector<int>> SobesOrig;
};

inline Result RemoveZero(vector<int>& v)
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

	auto nonOpt = solNonOpt();
	auto sobes = solSobes();
	auto sobesOrig = solSobesOrig();

	const bool b = get<0>(nonOpt);
	if (b != get<0>(sobes) || b != get<0>(sobesOrig))
		throw;

	if (!VerifyResult(get<2>(nonOpt)) || !VerifyResult(get<2>(sobes)) || !VerifyResult(get<2>(sobesOrig)))
		throw;

	if (!VectorCompare(get<2>(nonOpt), get<2>(sobes)) || !VectorCompare(get<2>(nonOpt), get<2>(sobesOrig)))
		throw;

	return Result{ move(nonOpt),move(sobes), move(sobesOrig) };
}

inline void RemoveTest(const size_t masLen, const int nonZeroValue)
{
	if (masLen == 0 || nonZeroValue == 0)
		throw;

	const auto getVectorSize = [masLen]
	{
		size_t result = 1;
		for (size_t k = 0; k < masLen; ++k)
			result *= 2;
		return result;
	};

	vector<Result> d;
	d.reserve(getVectorSize());
	for (vector<int>& v : VectorGenerator(masLen, nonZeroValue))
		d.emplace_back(RemoveZero(v));

	long long maxTimeNonOpt = 0, maxTimeSobes = 0, maxTimeSobesOrig = 0;
	long long maxNonOpt = 0, maxSobes = 0, maxSobesOrig = 0;
	long long timeNonOptMax = 0, timeSobesMax = 0, timeSobesOrigMax = 0;
	long long timeNonOptMin = LLONG_MAX, timeSobesMin = LLONG_MAX, timeSobesOrigMin = LLONG_MAX;
	for (const auto& v : d)
	{
		if (get<0>(v.NonOpt))
		{
			const long long t = get<1>(v.NonOpt);
			maxTimeNonOpt += t;
			if (timeNonOptMax < t)
				timeNonOptMax = t;
			if (timeNonOptMin > t)
				timeNonOptMin = t;
			++maxNonOpt;
		}
		if (get<0>(v.Sobes))
		{
			const long long t = get<1>(v.Sobes);
			maxTimeSobes += t;
			if (timeSobesMax < t)
				timeSobesMax = t;
			if (timeSobesMin > t)
				timeSobesMin = t;
			++maxSobes;
		}
		if (get<0>(v.SobesOrig))
		{
			const long long t = get<1>(v.SobesOrig);
			maxTimeSobesOrig += t;
			if (timeSobesOrigMax < t)
				timeSobesOrigMax = t;
			if (timeSobesOrigMin > t)
				timeSobesOrigMin = t;
			++maxSobesOrig;
		}
	}

	// ReSharper disable once CppAssignedValueIsNeverUsed
	maxTimeNonOpt /= maxNonOpt;
	// ReSharper disable once CppAssignedValueIsNeverUsed
	maxTimeSobes /= maxSobes;
	// ReSharper disable once CppAssignedValueIsNeverUsed
	maxTimeSobesOrig /= maxSobesOrig;
}

inline void YandexTest()
{
	{
		A* pa = new A();
		B* pb = new B();
		const Foo f(pa, pb);
		// ReSharper disable once CppDeclaratorNeverUsed
		const Foo d(f);
		//_asm int 3;
	}

	RemoveTest(3, 1);
}