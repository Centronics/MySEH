#pragma once
#include <vector>
#include <chrono>
#include <deque>
#include <optional>
#include <fstream>
#include <iostream>

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

inline size_t OnesCount(const vector<int>& v)
{
	size_t r = 0;
	for (const auto k : v)
		r += k != 0;
	return r;
}

class VectorGenerator
{
public:

	class Iterator
	{
		VectorGenerator* _this = nullptr;

	public:
		Iterator() = default;

		Iterator(VectorGenerator* cur) : _this(cur)
		{
			if (_this->_signVector.empty())
				_this = nullptr;
		}

		[[nodiscard]] const vector<int>& operator*() const
		{
			return _this->_signVector;
		}

		Iterator& operator++()
		{
			_this->Generate();
			if (_this->_signVector.empty())
				_this = nullptr;
			return *this;
		}

		[[nodiscard]] bool operator!=(const Iterator& iterator) const
		{
			return _this != iterator._this;
		}
	};

	VectorGenerator(const size_t masLen) : _signVector(masLen) { }

private:
	vector<int> _signVector;

	void Generate()
	{
		vector<int>::size_type k = _signVector.size();
		while (k--)
			if (int* t = &_signVector[k]; *t == 0)
			{
				*t = 1;
				int* lastElement = &_signVector[0] + _signVector.size();
				if (int* t1 = t + 1; t1 < lastElement)
					memset(t1, 0, (lastElement - t1) * sizeof(int));
				return;
			}
		_signVector.clear();
	}

public:
	// ReSharper disable once CppInconsistentNaming
	[[nodiscard]] Iterator begin()
	{
		return Iterator(this);
	}

	// ReSharper disable once CppMemberFunctionMayBeStatic
	// ReSharper disable once CppInconsistentNaming
	[[nodiscard]] Iterator end()
	{
		return Iterator();
	}
};

struct Result
{
	tuple<bool, long long, vector<int>> NonOpt;
	tuple<bool, long long, vector<int>> Sobes;
};

inline Result RemoveZero(vector<int>& v)
{
	//for (vector<int>::size_type k = v.size() - 1; k >= 0; --k) // Œ–»√»Õ¿À
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

	auto solNonOpt = [v]() mutable -> tuple<bool, long long, vector<int>>
	{
		if (v.empty())
			return tuple<bool, long long, vector<int>>();
		const auto getcomplexCount = [v]
		{
			size_t elemsHandlingCount = 0;
			for (vector<int>::size_type k = 0; k < v.size(); ++k)
				if (v[k] == 0)
					elemsHandlingCount += v.size() - k;
				else
					++elemsHandlingCount;
			return elemsHandlingCount;
		};
		size_t elemsHandlingCount = 0;
		const steady_clock::time_point start = steady_clock::now();
		for (auto k = v.begin(); k != v.end(); )
		{
			if (*k == 0)
			{
				elemsHandlingCount += v.size() - (k - v.begin());
				k = v.erase(k);
				continue;
			}
			++k;
			++elemsHandlingCount;
		}
		const steady_clock::time_point end = steady_clock::now();
		if (elemsHandlingCount != getcomplexCount())
			throw;
		return make_tuple(true, duration_cast<nanoseconds>(end - start).count(), v);
	};

	auto solSobes = [v]() mutable -> tuple<bool, long long, vector<int>>
	{
		if (v.empty())
			return tuple<bool, long long, vector<int>>();
		vector<int>::size_type lastZero = 0;
		bool needResize = false, needEnd = false;
		const vector<int>::size_type sz = v.size();
		vector<int>::size_type k = sz - 1;
		size_t elemsHandlingCount = 0;
		const steady_clock::time_point start = steady_clock::now();
		do
		{
			if (needResize && k == lastZero)
			{
				++elemsHandlingCount;
				if (v[k] != 0)
					++lastZero;
				needResize = true;
				break;
			}
			++elemsHandlingCount;
			if (v[k] == 0)
			{
				if (k != 0)
					continue;
				needResize = true;
				break;
			}
			vector<int>::size_type i = lastZero;
			for (; i < k; ++i)
			{
				++elemsHandlingCount;
				if (v[i] != 0)
					continue;
				v[i] = 1;
				v[k] = 0;
				lastZero = i + 1;
				needResize = true;
				if (k == lastZero)
					needEnd = true;
				break;
			}
			if (i == k)
			{
				lastZero = i + 1;
				needResize = true;
				break;
			}
		} while (!needEnd && k--);
		if (needResize)
			v.resize(lastZero);
		const steady_clock::time_point end = steady_clock::now();
		if (elemsHandlingCount != sz)
			throw;
		return make_tuple(true, duration_cast<nanoseconds>(end - start).count(), v);
	};

	auto nonOpt = solNonOpt();
	auto sobes = solSobes();

	if (get<0>(nonOpt) != get<0>(sobes))
		throw;

	if (!VerifyResult(get<2>(nonOpt)) || !VerifyResult(get<2>(sobes)))
		throw;

	if (!VectorCompare(get<2>(nonOpt), get<2>(sobes)))
		throw;

	if (OnesCount(v) != OnesCount(get<2>(sobes)))
		throw;

	return Result{ move(nonOpt),move(sobes) };
}

inline void RemoveTest(const size_t masLen, const bool writeToFile)
{
	if (masLen == 0)
		throw;

	const auto getVectorSize = [masLen]
	{
		size_t result = 1;
		for (size_t k = 0; k < masLen; ++k)
			result <<= 1;
		return result;
	};

	ofstream out;

	if (writeToFile)
	{
		out.open("D:\\Output.txt", std::ofstream::trunc);
		if (!out.is_open())
			throw;
	}

	const auto writeVectorToFile = [&out, writeToFile](const vector<int>& v)
	{
		if (!writeToFile)
			return;
		if (v.empty())
			out << "<empty>";
		else
			for (const auto i : v)
			{
				out << i;
				out << " ";
			}
	};

	const auto writeResultToFile = [&out, writeToFile, &writeVectorToFile](const tuple<bool, long long, vector<int>>& result, const char* comment)
	{
		if (!writeToFile)
			return;
		out << "=> " << comment << " = ";
		if (!get<0>(result))
		{
			out << "<empty>" << endl;
			return;
		}
		writeVectorToFile(get<2>(result));
		out << "=> Time = " << get<1>(result) << "ns" << endl;
	};

	vector<Result> d;
	d.reserve(getVectorSize());

	for (const vector<int>& v : VectorGenerator(masLen))
	{
		vector<int> t = v;
		if (writeToFile)
			out << "Source = ";
		writeVectorToFile(t);
		if (writeToFile)
			out << endl;
		Result result = RemoveZero(t);
		writeResultToFile(result.Sobes, "Sobes");
		writeResultToFile(result.NonOpt, "NonOpt");
		if (writeToFile)
			out << "--------------------------------------------------------------" << endl;
		d.emplace_back(result);
	}

	long long maxTimeNonOpt = 0, maxTimeSobes = 0;
	long long maxNonOpt = 0, maxSobes = 0;
	long long timeNonOptMax = 0, timeSobesMax = 0;
	long long timeNonOptMin = LLONG_MAX, timeSobesMin = LLONG_MAX;

	for (const auto& v : d)
	{
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
	}

	if (maxSobes != 0)
		maxTimeSobes /= maxSobes;
	if (maxNonOpt != 0)
		maxTimeNonOpt /= maxNonOpt;

	if (writeToFile)
	{
		out << endl << "<<< TEST START >>>" << endl;
		out << "Attempts \"Sobes\" = " << maxSobes << endl;
		out << "Max time \"Sobes\" = " << timeSobesMax << "ns" << endl;
		out << "Mid time \"Sobes\" = " << maxTimeSobes << "ns" << endl;
		out << "Min time \"Sobes\" = " << timeSobesMin << "ns" << endl;
		out << "--------------------------------------------------------------" << endl;
		out << "Attempts \"NonOpt\" = " << maxNonOpt << endl;
		out << "Max time \"NonOpt\" = " << timeNonOptMax << "ns" << endl;
		out << "Mid time \"NonOpt\" = " << maxTimeNonOpt << "ns" << endl;
		out << "Min time \"NonOpt\" = " << timeNonOptMin << "ns" << endl << "<<< END OF TEST >>>";
	}

	cout << "<<< TEST START >>>" << endl;
	cout << "Attempts \"Sobes\" = " << maxSobes << endl;
	cout << "Max time \"Sobes\" = " << timeSobesMax << "ns" << endl;
	cout << "Mid time \"Sobes\" = " << maxTimeSobes << "ns" << endl;
	cout << "Min time \"Sobes\" = " << timeSobesMin << "ns" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "Attempts \"NonOpt\" = " << maxNonOpt << endl;
	cout << "Max time \"NonOpt\" = " << timeNonOptMax << "ns" << endl;
	cout << "Mid time \"NonOpt\" = " << maxTimeNonOpt << "ns" << endl;
	cout << "Min time \"NonOpt\" = " << timeNonOptMin << "ns" << endl << "<<< END OF TEST >>>" << endl << endl;
}

inline void YandexTest(const bool writeToFile)
{
	{
		A* pa = new A();
		B* pb = new B();
		const Foo f(pa, pb);
		// ReSharper disable once CppDeclaratorNeverUsed
		const Foo d(f);  // NOLINT(performance-unnecessary-copy-initialization)
		//_asm int 3;
	}

	for (size_t k = 1; k <= 5; ++k)
		RemoveTest(k, writeToFile);
}